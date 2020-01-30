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
ECVL-EDDL interaction.
"""

import argparse
import sys

import pyecvl._core.ecvl as ecvl
import pyeddl._core.eddlT as eddlT


def main(args):
    img = ecvl.ImRead(args.in_img)
    print("Executing ImageToTensor")
    t = ecvl.ImageToTensor(img)
    eddlT.div_(t, 128)
    print("Executing TensorToImage")
    img = ecvl.TensorToImage(t)
    print("Executing TensorToView")
    ecvl.TensorToView(t)

    batch_size = 64
    print("Creating a DLDataset")
    d = ecvl.DLDataset(args.in_ds, batch_size, [28, 56], ecvl.ColorType.GRAY)
    print("Create x_train and y_train")
    x_train = eddlT.create(
        [batch_size, d.n_channels_, d.resize_dims_[0], d.resize_dims_[1]]
    )
    y_train = eddlT.create([batch_size, len(d.classes_)])

    # Load a batch of d.batch_size_ images into x_train and corresponding
    # labels in y_train. Images are resized to the dimensions specified in size
    print("Executing LoadBatch")
    d.LoadBatch(x_train, y_train)

    # Load test images in x_test and corresponding labels in y_test
    print("Executing TestToTensor")
    x_test, y_test = ecvl.TestToTensor(d, d.resize_dims_, ecvl.ColorType.GRAY)
    print("x_test info:")
    eddlT.info(x_test)
    print("y_test info:")
    eddlT.info(y_test)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("in_img", metavar="INPUT_IMAGE")
    parser.add_argument("in_ds", metavar="INPUT_DATASET")
    main(parser.parse_args(sys.argv[1:]))
