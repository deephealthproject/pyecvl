# Copyright (c) 2019-2021 CRS4
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

import pyecvl.ecvl as ecvl
from pyeddl.tensor import Tensor


AUG_TXT = '''\
SequentialAugmentationContainer
    AugRotate angle=[-5,5] center=(0,0) scale=0.5 interp="linear"
    AugAdditiveLaplaceNoise std_dev=[0,0.51]
    AugCoarseDropout p=[0,0.55] drop_size=[0.02,0.1] per_channel=0
    AugAdditivePoissonNoise lambda=[0,40]
    AugResizeDim dims=(30,30) interp="linear"
end
'''


def main(args):
    img = ecvl.ImRead(args.in_img)
    augs = ecvl.SequentialAugmentationContainer([
        ecvl.AugRotate([-5, 5]),
        ecvl.AugMirror(.5),
        ecvl.AugFlip(.5),
        ecvl.AugGammaContrast([3, 5]),
        ecvl.AugAdditiveLaplaceNoise([0, 0.2 * 255]),
        ecvl.AugCoarseDropout([0, 0.55], [0.02, 0.1], 0.5),
        ecvl.AugAdditivePoissonNoise([0, 40]),
        ecvl.AugResizeDim([500, 500]),
    ])
    ecvl.AugmentationParam.SetSeed(0)
    augs.Apply(img)
    print("Executing ImageToTensor")
    t = ecvl.ImageToTensor(img)
    t.div_(128)
    t.mult_(128)
    print("Executing TensorToImage")
    img = ecvl.TensorToImage(t)
    print("Executing TensorToView")
    ecvl.TensorToView(t)

    _ = ecvl.AugmentationFactory.create(AUG_TXT)

    training_augs = ecvl.SequentialAugmentationContainer([
        ecvl.AugRotate([-5, 5]),
        ecvl.AugAdditiveLaplaceNoise([0, 0.2 * 255]),
        ecvl.AugCoarseDropout([0, 0.55], [0.02, 0.1], 0),
        ecvl.AugAdditivePoissonNoise([0, 40]),
        ecvl.AugResizeDim([30, 30]),
    ])
    test_augs = ecvl.SequentialAugmentationContainer([
        ecvl.AugResizeDim([30, 30]),
    ])
    ds_augs = ecvl.DatasetAugmentations([training_augs, None, test_augs])

    batch_size = 64
    print("Creating a DLDataset")
    d = ecvl.DLDataset(args.in_ds, batch_size, ds_augs, ecvl.ColorType.GRAY)
    print("Create x and y")
    x = Tensor(
        [batch_size, d.n_channels_, d.resize_dims_[0], d.resize_dims_[1]]
    )
    y = Tensor([batch_size, len(d.classes_)])

    # Load a batch of d.batch_size_ images into x and corresponding labels
    # into y. Images are resized to the dimensions specified in the
    # augmentations chain
    print("Executing LoadBatch on training set")
    d.LoadBatch(x, y)

    # Change colortype and channels
    img = ecvl.TensorToImage(x)
    img.colortype_ = ecvl.ColorType.GRAY
    img.channels_ = "xyc"

    # Switch to Test split and load a batch of images
    print("Executing LoadBatch on test set")
    d.SetSplit(ecvl.SplitType.test)
    d.LoadBatch(x, y)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("in_img", metavar="INPUT_IMAGE")
    parser.add_argument("in_ds", metavar="INPUT_DATASET")
    main(parser.parse_args(sys.argv[1:]))
