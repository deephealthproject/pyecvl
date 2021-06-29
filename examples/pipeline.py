# Copyright (c) 2021 CRS4
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

"""\
Example pipeline.
"""

import argparse
import datetime
import time
import sys

import pyecvl.ecvl as ecvl
try:
    # make pyeddl types visible to ecvl functions that return them
    import pyeddl._core  # noqa
except ImportError:
    print("PyEDDL not installed - quitting")
    sys.exit(0)


def main(args):

    epochs = 5
    batch_size = 200
    num_workers = 4
    queue_ratio = 5

    training_augs = ecvl.SequentialAugmentationContainer([
        ecvl.AugRotate([-5, 5]),
        ecvl.AugAdditiveLaplaceNoise([0, 0.2 * 255]),
        ecvl.AugCoarseDropout([0, 0.55], [0.02, 0.1], 0),
        ecvl.AugAdditivePoissonNoise([0, 40]),
        ecvl.AugToFloat32(255),
    ])
    test_augs = ecvl.SequentialAugmentationContainer([
        ecvl.AugToFloat32(255),
    ])
    ecvl.AugmentationParam.SetSeed(0)
    ds_augs = ecvl.DatasetAugmentations([training_augs, test_augs])
    print("Creating a DLDataset")
    d = ecvl.DLDataset(args.in_ds, batch_size, ds_augs, ecvl.ColorType.GRAY,
                       ecvl.ColorType.none, num_workers, queue_ratio, [True, False])

    num_batches_training = d.GetNumBatches(ecvl.SplitType.training)
    num_batches_test = d.GetNumBatches(ecvl.SplitType.test)

    print("n. training batches:", num_batches_training)
    print("n. test batches:", num_batches_test)

    for i in range(epochs):
        tm_epoch = time.perf_counter()
        print("Starting training")
        d.SetSplit(ecvl.SplitType.training)
        d.ResetBatch(split=d.current_split_, shuffle=True)
        # Spawn the threads
        d.Start()
        for j in range(num_batches_training):
            tm = time.perf_counter()
            print(f"Epoch {i}/{epochs-1} (batch {j}/{num_batches_training-1}) - ", end="")
            print(f"|fifo| {d.GetQueueSize()} - ", end="")
            samples, x, y = d.GetBatch()
            # Sleep to simulate EDDL train_batch
            print("sleeping... - ", end="")
            d.sleep_for(datetime.timedelta(milliseconds=500))
            # eddl.train_batch(net, [x.get()], [y.get()])
            elapsed = time.perf_counter() - tm
            print(f"Elapsed time: {1e3*elapsed:.3f} ms")
        d.Stop()

        print("Starting test")
        d.SetSplit(ecvl.SplitType.test)
        # Reset current split without shuffling
        d.ResetBatch(d.current_split_, False)
        d.Start()
        for j in range(num_batches_test):
            tm = time.perf_counter()
            print(f"Test: Epoch {i}/{epochs-1} (batch {j}/{num_batches_test-1}) - ", end="")
            print(f"|fifo| {d.GetQueueSize()} - ", end="")
            _, x, y = d.GetBatch()

            # # Resize net for last batch
            # if j == num_batches_test - 1 and x.shape[0] != batch_size:
            #     # last mini-batch could have different size
            #     net.resize(x_batch)

            # Sleep to simulate EDDL evaluate_batch
            print("sleeping... - ", end="")
            d.sleep_for(datetime.timedelta(milliseconds=500))
            # eddl.eval_batch(net, [x.get()], [y.get()])

            elapsed = time.perf_counter() - tm
            print(f"Elapsed time: {1e3*elapsed:.3f} ms")
        d.Stop()

        elapsed = time.perf_counter() - tm_epoch
        print(f"Epoch elapsed time: {elapsed:.3f} s")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("in_ds", metavar="INPUT_DATASET")
    main(parser.parse_args(sys.argv[1:]))
