# Copyright (c) 2020 CRS4
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
MNIST batch training.
"""

import argparse
import random
import sys

import pyecvl.ecvl as ecvl
import pyeddl.eddl as eddl
import pyeddl.eddlT as eddlT
from models import LeNet


def main(args):
    num_classes = 10
    size = [28, 28]  # size of images
    ctype = ecvl.ColorType.GRAY

    in_ = eddl.Input([1, size[0], size[1]])
    out = LeNet(in_, num_classes)
    net = eddl.Model([in_], [out])
    eddl.build(
        net,
        eddl.sgd(0.001, 0.9),
        ["soft_cross_entropy"],
        ["categorical_accuracy"],
        eddl.CS_GPU([1]) if args.gpu else eddl.CS_CPU()
    )
    eddl.summary(net)
    eddl.setlogfile(net, "mnist")

    training_augs = ecvl.SequentialAugmentationContainer([
        ecvl.AugRotate([-5, 5]),
        ecvl.AugAdditivePoissonNoise([0, 10]),
        ecvl.AugGaussianBlur([0, 0.8]),
        ecvl.AugCoarseDropout([0, 0.3], [0.02, 0.05], 0),
    ])
    dataset_augs = ecvl.DatasetAugmentations([training_augs, None, None])

    print("Reading dataset")
    d = ecvl.DLDataset(args.in_ds, args.batch_size, dataset_augs, ctype)
    x_train = eddlT.create([args.batch_size, d.n_channels_, size[0], size[1]])
    y_train = eddlT.create([args.batch_size, len(d.classes_)])
    num_samples = len(d.GetSplit())
    num_batches = num_samples // args.batch_size
    indices = list(range(args.batch_size))

    print("Training")
    for i in range(args.epochs):
        eddl.reset_loss(net)
        s = d.GetSplit()
        random.shuffle(s)
        d.split_.training_ = s
        d.ResetCurrentBatch()
        for j in range(num_batches):
            print("Epoch %d/%d (batch %d/%d) - " %
                  (i + 1, args.epochs, j + 1, num_batches), end="", flush=True)
            d.LoadBatch(x_train, y_train)
            x_train.div_(255.0)
            tx, ty = [x_train], [y_train]
            eddl.train_batch(net, tx, ty, indices)
            eddl.print_loss(net, j)
            print()

    print("Saving weights")
    eddl.save(net, "mnist_checkpoint.bin", "bin")

    print("Evaluation")
    d.SetSplit(ecvl.SplitType.test)
    num_samples = len(d.GetSplit())
    num_batches = num_samples // args.batch_size
    for i in range(num_batches):
        print("batch %d / %d - " % (i, num_batches), end="", flush=True)
        d.LoadBatch(x_train, y_train)
        x_train.div_(255.0)
        eddl.evaluate(net, [x_train], [y_train])


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("in_ds", metavar="INPUT_DATASET")
    parser.add_argument("--epochs", type=int, metavar="INT", default=5)
    parser.add_argument("--batch-size", type=int, metavar="INT", default=64)
    parser.add_argument("--gpu", action="store_true")
    main(parser.parse_args(sys.argv[1:]))
