"""\
Skin lesion segmentation example.
"""

import argparse
import os
import random
import sys

import numpy as np
import pyecvl._core.ecvl as ecvl
import pyeddl._core.eddl as eddl
import pyeddl._core.eddlT as eddlT
from models import SegNet


class Evaluator():

    def __init__(self):
        self.eps = 1e-06
        self.buf = []

    def ResetEval(self):
        self.buf = []

    def BinaryIoU(self, a, b):
        intersection = np.logical_and(a >= 0.5, b >= 0.5).sum()
        union = np.logical_or(a >= 0.5, b >= 0.5).sum()
        rval = (intersection + self.eps) / (union + self.eps)
        self.buf.append(rval)
        return rval

    def MIoU(self):
        if not self.buf:
            return 0
        return sum(self.buf) / len(self.buf)


def ImageSqueeze(img):
    k = img.dims_.index(1)
    img.dims_ = [_ for i, _ in enumerate(img.dims_) if i != k]
    img.strides_ = [_ for i, _ in enumerate(img.strides_) if i != k]
    k = img.channels_.find("z")
    img.channels_ = "".join([_ for i, _ in enumerate(img.channels_) if i != k])


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
        eddl.CS_GPU([1]) if args.gpu else eddl.CS_CPU()
    )
    eddl.summary(net)

    print("Reading dataset")
    d = ecvl.DLDataset(args.in_ds, args.batch_size, size)
    x = eddlT.create([args.batch_size, d.n_channels_, size[0], size[1]])
    y = eddlT.create([args.batch_size, 1, size[0], size[1]])
    num_samples = len(d.GetSplit())
    num_batches = num_samples // args.batch_size
    d.SetSplit("validation")
    num_samples_validation = len(d.GetSplit())
    num_batches_validation = num_samples_validation // args.batch_size
    indices = list(range(args.batch_size))

    if args.out_dir:
        try:
            os.makedirs(args.out_dir)
        except FileExistsError:
            pass
    evaluator = Evaluator()
    print("Starting training")
    for i in range(args.epochs):
        d.SetSplit("training")
        eddl.reset_loss(net)
        s = d.GetSplit()
        random.shuffle(s)
        d.split_.training_ = s
        d.ResetAllBatches()
        for j in range(num_batches):
            print("Epoch %d/%d (batch %d/%d) - " %
                  (i + 1, args.epochs, j + 1, num_batches), end="", flush=True)
            d.LoadBatch(x, y)
            x.div_(255.0)
            y.div_(255.0)
            tx, ty = [x], [y]
            eddl.train_batch(net, tx, ty, indices)
            eddl.print_loss(net, j)
            print()
        d.SetSplit("validation")
        evaluator.ResetEval()
        for j in range(num_batches_validation):
            print("Validation - Epoch %d/%d (batch %d/%d) " %
                  (i + 1, args.epochs, j + 1, num_batches_validation),
                  end="", flush=True)
            d.LoadBatch(x, y)
            x.div_(255.0)
            y.div_(255.0)
            eddl.forward(net, [x])
            output = eddl.getTensor(out_sigm)
            for k in range(args.batch_size):
                img = eddlT.select(output, k)
                gt = eddlT.select(y, k)
                a, b = np.array(img, copy=False), np.array(gt, copy=False)
                iou = evaluator.BinaryIoU(a, b)
                print("- IoU: %.6g " % iou, end="", flush=True)
                if (args.out_dir):
                    img_t = ecvl.TensorToView(img)
                    ImageSqueeze(img_t)
                    img.mult_(255.)
                    output_fn = os.path.join(
                        args.out_dir, "batch_%d_output.png" % j
                    )
                    ecvl.ImWrite(output_fn, img_t)
                    if i == 0:
                        gt_t = ecvl.TensorToView(gt)
                        ImageSqueeze(gt_t)
                        gt.mult_(255.)
                        gt_fn = os.path.join(
                            args.out_dir, "batch_%d_gt.png" % j
                        )
                        ecvl.ImWrite(gt_fn, gt_t)
            print()
        print("MIoU: %.6g" % evaluator.MIoU())


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("in_ds", metavar="INPUT_DATASET")
    parser.add_argument("--epochs", type=int, metavar="INT", default=20)
    parser.add_argument("--batch-size", type=int, metavar="INT", default=2)
    parser.add_argument("--gpu", action="store_true")
    parser.add_argument("--out-dir", metavar="DIR", help="save images here")
    main(parser.parse_args(sys.argv[1:]))
