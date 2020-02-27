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
Skin lesion classification inference example.

More information and checkpoints available at
https://github.com/deephealthproject/use_case_pipeline
"""

import argparse

import numpy as np
import os
import pyecvl._core.ecvl as ecvl
import pyeddl._core.eddl as eddl
import pyeddl._core.eddlT as eddlT

import utils
from models import VGG16


def main(args):
    num_classes = 8
    size = [224, 224]  # size of images

    if args.out_dir:
        # Create output folders, one for each class
        for x in range(num_classes):
            os.makedirs('{}/{}'.format(args.out_dir, x), exist_ok=True)

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

    if not os.path.exists(args.ckpts):
        print('Checkpoint "{}" must exist.'.format(args.ckpts))
        exit(1)
    eddl.load(net, args.ckpts, "bin")

    eddl.summary(net)

    print("Reading dataset")
    d = ecvl.DLDataset(args.in_ds, args.batch_size, size)
    x_train = eddlT.create([args.batch_size, d.n_channels_, size[0], size[1]])
    y_train = eddlT.create([args.batch_size, len(d.classes_)])

    print("Testing")
    d.SetSplit("test")
    num_samples = len(d.GetSplit())
    num_batches = num_samples // args.batch_size
    d.ResetCurrentBatch()
    for b in range(num_batches):
        print("Batch {:d}/{:d} - ".format(b + 1, num_batches), end="",
              flush=True)

        d.LoadBatch(x_train, y_train)
        x_train.div_(255.0)
        eddl.forward(net, [x_train])
        if args.out_dir:
            # Save network predictions
            for j in range(args.batch_size):
                pred = eddlT.select(eddl.getTensor(out), j)
                gt = eddlT.select(y_train, j)
                image = eddlT.select(x_train, j)
                pred = np.array(pred, copy=False)
                gt = np.array(gt, copy=False)

                image.mult_(255.)
                gt = np.argmax(gt).item()
                pred = np.argmax(pred).item()
                image_Im = ecvl.TensorToImage(image)
                utils.ImageSqueeze(image_Im)
                ecvl.ImWrite('{}/{}/img_{}_gt_class_{}.png'.format(
                    args.out_dir, pred, j + b * args.batch_size, gt),
                             image_Im)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("in_ds", metavar="INPUT_DATASET")
    parser.add_argument("ckpts", metavar='CHECKPOINTS_PATH',
                        default='./isic_class_VGG16_sgd_lr_0.001_momentum'
                        '_0.9_loss_sce_size_224_epoch_48.bin')
    parser.add_argument("--batch-size", type=int, metavar="INT", default=12)
    parser.add_argument("--gpu", action="store_true")
    parser.add_argument("--out-dir", metavar="DIR", help="save images here")
    main(parser.parse_args())
