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
Skin lesion segmentation training example.

More information and checkpoints available at https://github.com/deephealthproject/use_case_pipeline
"""

import argparse

import numpy as np
import os
import pyecvl._core.ecvl as ecvl
import pyeddl._core.eddl as eddl
import pyeddl._core.eddlT as eddlT
import random

import utils
from models import SegNet


def main(args):
    num_classes = 1
    size = [192, 192]  # size of images

    in_ = eddl.Input([3, size[0], size[1]])
    out = SegNet(in_, num_classes)
    out_sigm = eddl.Sigmoid(out)
    net = eddl.Model([in_], [out_sigm])
    eddl.build(
        net,
        eddl.adam(0.0001),
        ["cross_entropy"],
        ["mean_squared_error"],
    )

    if args.gpu:
        eddl.toGPU(net, [1])

    eddl.summary(net)

    print("Reading dataset")
    d = ecvl.DLDataset(args.in_ds, args.batch_size, size)
    x = eddlT.create([args.batch_size, d.n_channels_, size[0], size[1]])
    y = eddlT.create([args.batch_size, 1, size[0], size[1]])
    num_samples_train = len(d.GetSplit())
    num_batches_train = num_samples_train // args.batch_size
    d.SetSplit("validation")
    num_samples_validation = len(d.GetSplit())
    num_batches_validation = num_samples_validation // args.batch_size
    indices = list(range(args.batch_size))

    if args.out_dir:
        try:
            os.makedirs(args.out_dir)
        except FileExistsError:
            pass
    evaluator = utils.Evaluator()
    best_miou = 0.
    print("Starting training")
    for e in range(args.epochs):
        print("Epoch {:d}/{:d} - Training".format(e + 1, args.epochs), flush=True)
        d.SetSplit("training")
        eddl.reset_loss(net)
        s = d.GetSplit()
        random.shuffle(s)
        d.split_.training_ = s
        d.ResetAllBatches()
        for b in range(num_batches_train):
            print("Epoch {:d}/{:d} (batch {:d}/{:d}) - ".format(e + 1, args.epochs, b + 1, num_batches_train), end="",
                  flush=True)
            d.LoadBatch(x, y)
            x.div_(255.0)
            y.div_(255.0)
            tx, ty = [x], [y]
            eddl.train_batch(net, tx, ty, indices)
            eddl.print_loss(net, b)
            print()
        d.SetSplit("validation")
        evaluator.ResetEval()
        print("Epoch %d/%d - Evaluation" % (e + 1, args.epochs), flush=True)
        for b in range(num_batches_validation):
            print("Epoch {:d}/{:d} (batch {:d}/{:d}) ".format(e + 1, args.epochs, b + 1, num_batches_validation),
                  end="", flush=True)
            d.LoadBatch(x, y)
            x.div_(255.0)
            y.div_(255.0)
            eddl.forward(net, [x])
            output = eddl.getTensor(out_sigm)
            for k in range(args.batch_size):
                img = eddlT.select(output, k)
                gt = eddlT.select(y, k)
                img_np, gt_np = np.array(img, copy=False), np.array(gt, copy=False)
                iou = evaluator.BinaryIoU(img_np, gt_np)
                print("- IoU: %.6g " % iou, end="", flush=True)
                if args.out_dir:
                    img_np[img_np >= 0.5] = 1
                    img_np[img_np < 0.5] = 0
                    img_t = ecvl.TensorToView(img)
                    utils.ImageSqueeze(img_t)
                    img.mult_(255.)
                    output_fn = os.path.join(
                        args.out_dir, "batch_%d_%d_output.png" % (b, k)
                    )
                    ecvl.ImWrite(output_fn, img_t)
                    if e == 0:
                        gt_t = ecvl.TensorToView(gt)
                        utils.ImageSqueeze(gt_t)
                        gt.mult_(255.)
                        gt_fn = os.path.join(
                            args.out_dir, "batch_%d_%d_gt.png" % (b, k)
                        )
                        ecvl.ImWrite(gt_fn, gt_t)
            print()
        current_miou = evaluator.MIoU()
        print("MIoU: %.6g" % current_miou)
        if best_miou < current_miou:
            best_miou = current_miou
            eddl.save(net, "isic_segm_checkpoint.bin", "bin")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("in_ds", metavar="INPUT_DATASET")
    parser.add_argument("--epochs", type=int, metavar="INT", default=20)
    parser.add_argument("--batch-size", type=int, metavar="INT", default=8)
    parser.add_argument("--gpu", action="store_true")
    parser.add_argument("--out-dir", metavar="DIR", help="save images here")
    main(parser.parse_args())
