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
Skin lesion segmentation inference example.

More information and checkpoints available at
https://github.com/deephealthproject/use_case_pipeline
"""

import argparse

import numpy as np
import os
import pyecvl.ecvl as ecvl
import pyeddl.eddl as eddl
import pyeddl.eddlT as eddlT

import utils
from models import SegNet


def main(args):
    num_classes = 1
    size = [192, 192]  # size of images
    thresh = 0.5

    if args.out_dir:
        os.makedirs(args.out_dir, exist_ok=True)

    in_ = eddl.Input([3, size[0], size[1]])
    out = SegNet(in_, num_classes)
    out_sigm = eddl.Sigmoid(out)
    net = eddl.Model([in_], [out_sigm])
    eddl.build(
        net,
        eddl.adam(0.0001),
        ["cross_entropy"],
        ["mean_squared_error"],
        eddl.CS_GPU([1]) if args.gpu else eddl.CS_CPU()
    )
    eddl.summary(net)
    eddl.setlogfile(net, "skin_lesion_segmentation_inference")

    if not os.path.exists(args.ckpts):
        raise RuntimeError('Checkpoint "{}" not found'.format(args.ckpts))
    eddl.load(net, args.ckpts, "bin")

    training_augs = ecvl.SequentialAugmentationContainer([
        ecvl.AugResizeDim(size),
    ])
    test_augs = ecvl.SequentialAugmentationContainer([
        ecvl.AugResizeDim(size),
    ])
    dataset_augs = ecvl.DatasetAugmentations([training_augs, None, test_augs])

    print("Reading dataset")
    d = ecvl.DLDataset(args.in_ds, args.batch_size, dataset_augs)
    x = eddlT.create([args.batch_size, d.n_channels_, size[0], size[1]])
    y = eddlT.create([args.batch_size, d.n_channels_gt_, size[0], size[1]])
    print("Testing")
    d.SetSplit(ecvl.SplitType.test)
    num_samples_test = len(d.GetSplit())
    num_batches_test = num_samples_test // args.batch_size

    evaluator = utils.Evaluator()
    evaluator.ResetEval()
    for b in range(num_batches_test):
        n = 0
        print("Batch {:d}/{:d} ".format(
            b + 1, num_batches_test), end="", flush=True)
        d.LoadBatch(x, y)
        x.div_(255.0)
        y.div_(255.0)
        eddl.forward(net, [x])
        output = eddl.getTensor(out_sigm)
        for k in range(args.batch_size):
            img = eddlT.select(output, k)
            gt = eddlT.select(y, k)
            img_np, gt_np = np.array(img, copy=False), np.array(gt, copy=False)
            iou = evaluator.BinaryIoU(img_np, gt_np, thresh=thresh)
            print("- IoU: %.6g " % iou, end="", flush=True)
            if args.out_dir:
                # C++ BinaryIoU modifies image as a side effect
                img_np[img_np >= thresh] = 1
                img_np[img_np < thresh] = 0
                img_t = ecvl.TensorToView(img)
                img_t.colortype_ = ecvl.ColorType.GRAY
                img_t.channels_ = "xyc"
                img.mult_(255.)
                # orig_img
                orig_img = eddlT.select(x, k)
                orig_img.mult_(255.)
                orig_img_t = ecvl.TensorToImage(orig_img)
                orig_img_t.colortype_ = ecvl.ColorType.BGR
                orig_img_t.channels_ = "xyc"

                tmp, labels = ecvl.Image.empty(), ecvl.Image.empty()
                ecvl.CopyImage(img_t, tmp, ecvl.DataType.uint8)
                ecvl.ConnectedComponentsLabeling(tmp, labels)
                ecvl.CopyImage(labels, tmp, ecvl.DataType.uint8)
                contours = ecvl.FindContours(tmp)
                ecvl.CopyImage(orig_img_t, tmp, ecvl.DataType.uint8)
                tmp_np = np.array(tmp, copy=False)
                for cseq in contours:
                    for c in cseq:
                        tmp_np[c[0], c[1], 0] = 0
                        tmp_np[c[0], c[1], 1] = 0
                        tmp_np[c[0], c[1], 2] = 255

                filename = d.samples_[d.GetSplit()[n]].location_[0]
                head, tail = os.path.splitext(os.path.basename(filename))
                bname = "%s.png" % head
                output_fn = os.path.join(args.out_dir, bname)
                ecvl.ImWrite(output_fn, tmp)

                gt_t = ecvl.TensorToView(gt)
                gt_t.colortype_ = ecvl.ColorType.GRAY
                gt_t.channels_ = "xyc"
                gt.mult_(255.)
                gt_filename = d.samples_[d.GetSplit()[n]].label_path_
                gt_fn = os.path.join(
                    args.out_dir, os.path.basename(gt_filename)
                )
                ecvl.ImWrite(gt_fn, gt_t)
            n += 1
        print()
    print("MIoU: %.6g" % evaluator.MeanMetric())


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("in_ds", metavar="INPUT_DATASET")
    parser.add_argument("ckpts", metavar='CHECKPOINTS_PATH',
                        default='./isic_segm_segnet_adam_lr_0.0001_loss_'
                        'ce_size_192_epoch_24.bin')
    parser.add_argument("--batch-size", type=int, metavar="INT", default=8)
    parser.add_argument("--gpu", action="store_true")
    parser.add_argument("--out-dir", metavar="DIR",
                        help="if set, save images in this directory")
    main(parser.parse_args())
