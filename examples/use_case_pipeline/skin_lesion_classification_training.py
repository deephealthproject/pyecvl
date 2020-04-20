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

More information and checkpoints available at
https://github.com/deephealthproject/use_case_pipeline
"""

import argparse
import os

import numpy as np
import pyecvl.ecvl as ecvl
import pyeddl.eddl as eddl
import pyeddl.eddlT as eddlT
import random

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
    eddl.setlogfile(net, "skin_lesion_classification")

    training_augs = ecvl.SequentialAugmentationContainer([
        ecvl.AugResizeDim(size),
        ecvl.AugMirror(.5),
        ecvl.AugFlip(.5),
        ecvl.AugRotate([-180, 180]),
        ecvl.AugAdditivePoissonNoise([0, 10]),
        ecvl.AugGammaContrast([0.5, 1.5]),
        ecvl.AugGaussianBlur([0, 0.8]),
        ecvl.AugCoarseDropout([0, 0.3], [0.02, 0.05], 0.5)
    ])
    validation_augs = ecvl.SequentialAugmentationContainer([
        ecvl.AugResizeDim(size),
    ])
    dataset_augs = ecvl.DatasetAugmentations(
        [training_augs, validation_augs, None]
    )

    print("Reading dataset")
    d = ecvl.DLDataset(args.in_ds, args.batch_size, dataset_augs)
    x = eddlT.create([args.batch_size, d.n_channels_, size[0], size[1]])
    y = eddlT.create([args.batch_size, len(d.classes_)])
    num_samples_train = len(d.GetSplit())
    num_batches_train = num_samples_train // args.batch_size
    d.SetSplit(ecvl.SplitType.validation)
    num_samples_val = len(d.GetSplit())
    num_batches_val = num_samples_val // args.batch_size
    indices = list(range(args.batch_size))
    metric = eddl.getMetric("categorical_accuracy")

    print("Starting training")
    for e in range(args.epochs):
        print("Epoch {:d}/{:d} - Training".format(e + 1, args.epochs),
              flush=True)
        if args.out_dir:
            current_path = os.path.join(args.out_dir, "Epoch_%d" % e)
            for c in d.classes_:
                c_dir = os.path.join(current_path, c)
                os.makedirs(c_dir, exist_ok=True)
        d.SetSplit(ecvl.SplitType.training)
        eddl.reset_loss(net)
        total_metric = []
        s = d.GetSplit()
        random.shuffle(s)
        d.split_.training_ = s
        d.ResetAllBatches()
        for b in range(num_batches_train):
            print("Epoch {:d}/{:d} (batch {:d}/{:d}) - ".format(
                e + 1, args.epochs, b + 1, num_batches_train
            ), end="", flush=True)
            d.LoadBatch(x, y)
            x.div_(255.0)
            tx, ty = [x], [y]
            eddl.train_batch(net, tx, ty, indices)
            eddl.print_loss(net, b)
            print()

        print("Saving weights")
        eddl.save(
            net, "isic_classification_checkpoint_epoch_%s.bin" % e, "bin"
        )

        print("Epoch %d/%d - Evaluation" % (e + 1, args.epochs), flush=True)
        d.SetSplit(ecvl.SplitType.validation)
        for b in range(num_batches_val):
            n = 0
            print("Epoch {:d}/{:d} (batch {:d}/{:d}) - ".format(
                e + 1, args.epochs, b + 1, num_batches_val
            ), end="", flush=True)
            d.LoadBatch(x, y)
            x.div_(255.0)
            eddl.forward(net, [x])
            output = eddl.getTensor(out)
            sum_ = 0.0
            for k in range(args.batch_size):
                result = eddlT.select(output, k)
                target = eddlT.select(y, k)
                ca = metric.value(target, result)
                total_metric.append(ca)
                sum_ += ca
                if args.out_dir:
                    result_a = np.array(result, copy=False)
                    target_a = np.array(target, copy=False)
                    classe = np.argmax(result_a).item()
                    gt_class = np.argmax(target_a).item()
                    single_image = eddlT.select(x, k)
                    img_t = ecvl.TensorToView(single_image)
                    img_t.colortype_ = ecvl.ColorType.BGR
                    single_image.mult_(255.)
                    filename = d.samples_[d.GetSplit()[n]].location_[0]
                    head, tail = os.path.splitext(os.path.basename(filename))
                    bname = "%s_gt_class_%s.png" % (head, gt_class)
                    cur_path = os.path.join(
                        current_path, d.classes_[classe], bname
                    )
                    ecvl.ImWrite(cur_path, img_t)
                n += 1
            print("categorical_accuracy:", sum_ / args.batch_size)
        total_avg = sum(total_metric) / len(total_metric)
        print("Total categorical accuracy:", total_avg)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("in_ds", metavar="INPUT_DATASET")
    parser.add_argument("--epochs", type=int, metavar="INT", default=50)
    parser.add_argument("--batch-size", type=int, metavar="INT", default=12)
    parser.add_argument("--gpu", action="store_true")
    parser.add_argument("--out-dir", metavar="DIR",
                        help="if set, save images in this directory")
    main(parser.parse_args())
