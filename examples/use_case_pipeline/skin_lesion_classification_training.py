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
Skin lesion classification training example.

More information and checkpoints available at https://github.com/deephealthproject/use_case_pipeline
"""

import argparse

import pyecvl._core.ecvl as ecvl
import pyeddl._core.eddl as eddl
import pyeddl._core.eddlT as eddlT
import random

from examples.use_case_pipeline.models import VGG16


def main(args):
    num_classes = 8
    size = [224, 224]  # size of images

    in_ = eddl.Input([3, size[0], size[1]])
    out = VGG16(in_, num_classes)
    net = eddl.Model([in_], [out])
    eddl.build(
        net,
        eddl.sgd(0.0001, 0.9),
        ["soft_cross_entropy"],
        ["categorical_accuracy"],
    )

    if args.gpu:
        eddl.toGPU(net, [1])

    eddl.summary(net)

    print("Reading dataset")
    d = ecvl.DLDataset(args.in_ds, args.batch_size, size)
    x_train = eddlT.create([args.batch_size, d.n_channels_, size[0], size[1]])
    y_train = eddlT.create([args.batch_size, len(d.classes_)])
    num_samples_train = len(d.GetSplit())
    num_batches_train = num_samples_train // args.batch_size
    d.SetSplit("validation")
    num_samples_val = len(d.GetSplit())
    num_batches_val = num_samples_val // args.batch_size
    indices = list(range(args.batch_size))

    for e in range(args.epochs):
        print("Epoch {:d}/{:d} - Training".format(e + 1, args.epochs), flush=True)
        d.SetSplit("training")
        eddl.reset_loss(net)
        s = d.GetSplit()
        random.shuffle(s)
        d.split_.training_ = s
        d.ResetCurrentBatch()
        for b in range(num_batches_train):
            print("Epoch {:d}/{:d} (batch {:d}/{:d}) - ".format(e + 1, args.epochs, b + 1, num_batches_train), end="",
                  flush=True)
            d.LoadBatch(x_train, y_train)
            x_train.div_(255.0)
            tx, ty = [x_train], [y_train]
            eddl.train_batch(net, tx, ty, indices)
            eddl.print_loss(net, b)
            print()

        print("Epoch %d/%d - Evaluation" % (e + 1, args.epochs), flush=True)
        d.SetSplit("validation")
        d.ResetCurrentBatch()
        for b in range(num_batches_val):
            print("Epoch {:d}/{:d} (batch {:d}/{:d}) - ".format(e + 1, args.epochs, b + 1, num_batches_val), end="",
                  flush=True)
            d.LoadBatch(x_train, y_train)
            x_train.div_(255.0)
            eddl.evaluate(net, [x_train], [y_train])

    eddl.save(net, "isic_class_checkpoint.bin", "bin")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("in_ds", metavar="INPUT_DATASET")
    parser.add_argument("--epochs", type=int, metavar="INT", default=50)
    parser.add_argument("--batch-size", type=int, metavar="INT", default=12)
    parser.add_argument("--gpu", action="store_true")
    main(parser.parse_args())
