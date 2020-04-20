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
import pyecvl.ecvl as ecvl
import pyeddl.eddl as eddl
import pyeddl.eddlT as eddlT

from models import VGG16


def main(args):
    num_classes = 8
    size = [224, 224]  # size of images

    in_ = eddl.Input([3, size[0], size[1]])
    out = VGG16(in_, num_classes)
    net = eddl.Model([in_], [out])
    eddl.build(
        net,
        eddl.sgd(0.001, 0.9),
        ["soft_cross_entropy"],
        ["categorical_accuracy"],
        eddl.CS_GPU([1]) if args.gpu else eddl.CS_CPU()
    )
    eddl.summary(net)
    eddl.setlogfile(net, "skin_lesion_classification_inference")

    training_augs = ecvl.SequentialAugmentationContainer([
        ecvl.AugResizeDim(size),
    ])
    test_augs = ecvl.SequentialAugmentationContainer([
        ecvl.AugResizeDim(size),
    ])
    dataset_augs = ecvl.DatasetAugmentations([training_augs, None, test_augs])

    print("Reading dataset")
    d = ecvl.DLDataset(args.in_ds, args.batch_size, dataset_augs)

    if args.out_dir:
        for c in d.classes_:
            os.makedirs(os.path.join(args.out_dir, c), exist_ok=True)

    x = eddlT.create([args.batch_size, d.n_channels_, size[0], size[1]])
    y = eddlT.create([args.batch_size, len(d.classes_)])

    d.SetSplit(ecvl.SplitType.test)
    num_samples = len(d.GetSplit())
    num_batches = num_samples // args.batch_size
    metric = eddl.getMetric("categorical_accuracy")
    total_metric = []

    if not os.path.exists(args.ckpts):
        raise RuntimeError('Checkpoint "{}" not found'.format(args.ckpts))
    eddl.load(net, args.ckpts, "bin")

    print("Testing")
    for b in range(num_batches):
        n = 0
        print("Batch {:d}/{:d}".format(b + 1, num_batches))
        d.LoadBatch(x, y)
        x.div_(255.0)
        eddl.forward(net, [x])
        output = eddl.getTensor(out)
        sum_ = 0.0
        for j in range(args.batch_size):
            result = eddlT.select(output, j)
            target = eddlT.select(y, j)
            ca = metric.value(target, result)
            total_metric.append(ca)
            sum_ += ca
            if args.out_dir:
                result_a = np.array(result, copy=False)
                target_a = np.array(target, copy=False)
                classe = np.argmax(result_a).item()
                gt_class = np.argmax(target_a).item()
                single_image = eddlT.select(x, j)
                img_t = ecvl.TensorToView(single_image)
                img_t.colortype_ = ecvl.ColorType.BGR
                single_image.mult_(255.)
                filename = d.samples_[d.GetSplit()[n]].location_[0]
                head, tail = os.path.splitext(os.path.basename(filename))
                bname = "%s_gt_class_%s.png" % (head, gt_class)
                cur_path = os.path.join(
                    args.out_dir, d.classes_[classe], bname
                )
                ecvl.ImWrite(cur_path, img_t)
            n += 1
        print("categorical_accuracy:", sum_ / args.batch_size)
    total_avg = sum(total_metric) / len(total_metric)
    print("Total categorical accuracy:", total_avg)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("in_ds", metavar="INPUT_DATASET")
    parser.add_argument("ckpts", metavar='CHECKPOINTS_PATH',
                        default='./isic_class_VGG16_sgd_lr_0.001_momentum'
                        '_0.9_loss_sce_size_224_epoch_48.bin')
    parser.add_argument("--batch-size", type=int, metavar="INT", default=12)
    parser.add_argument("--gpu", action="store_true")
    parser.add_argument("--out-dir", metavar="DIR",
                        help="if set, save images in this directory")
    main(parser.parse_args())
