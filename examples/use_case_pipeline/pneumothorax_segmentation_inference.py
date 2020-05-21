# PyECVL - Python wrapper for European Computer Vision Library
# Copyright (c) 2020, Università degli Studi di Modena e Reggio Emilia
# (UNIMORE), AImageLab
# Authors:
#    Michele Cancilla (michele.cancilla@unimore.it)
#    Laura Canalini (laura.canalini@unimore.it)
#    Costantino Grana (costantino.grana@unimore.it)
#    Federico Bolelli (federico.bolelli@unimore.it)
#    Stefano Allegretti (stefano.allegretti@unimore.it)
# All rights reserved.

"""\
Pneumothorax segmentation inference example.

More information and checkpoints available at
https://github.com/deephealthproject/use_case_pipeline
"""

import argparse
import os

import pyeddl.eddl as eddl
import pyeddl.eddlT as eddlT
import pyecvl.ecvl as ecvl

import utils
from models import SegNetBN


def main(args):
    num_classes = 1
    size = [512, 512]  # size of images
    thresh = 0.5

    if args.out_dir:
        os.makedirs(args.out_dir, exist_ok=True)

    in_ = eddl.Input([1, size[0], size[1]])
    out = SegNetBN(in_, num_classes)
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
    eddl.setlogfile(net, "pneumothorax_segmentation_inference")

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
    d = ecvl.DLDataset(args.in_ds, args.batch_size, dataset_augs,
                       ecvl.ColorType.GRAY)
    x = eddlT.create([args.batch_size, d.n_channels_, size[0], size[1]])
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
        d.LoadBatch(x)
        x.div_(255.0)
        eddl.forward(net, [x])
        if args.out_dir:
            output = eddl.getTensor(out_sigm)
            for k in range(args.batch_size):
                img = eddlT.select(output, k)
                img_I = ecvl.TensorToImage(img)
                img_I.colortype_ = ecvl.ColorType.GRAY
                img_I.channels_ = "xyc"
                ecvl.Threshold(img_I, img_I, thresh, 255)

                filename = d.samples_[d.GetSplit()[n]].location_[0]
                head, tail = os.path.splitext(os.path.basename(filename))
                bname = "{}.png".format(head)
                output_fn = os.path.join(args.out_dir, bname)
                ecvl.ImWrite(output_fn, img_I)

                n += 1
        print()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("in_ds", metavar="INPUT_DATASET")
    parser.add_argument("ckpts", metavar='CHECKPOINTS_PATH',
                        default='./pneumothorax_segnetBN_adam_lr_0.0001_loss_'
                                'ce_size_512_epoch_44.bin')
    parser.add_argument("--batch-size", type=int, metavar="INT", default=8)
    parser.add_argument("--gpu", action="store_true")
    parser.add_argument("--out-dir", metavar="DIR",
                        help="if set, save images in this directory")
    main(parser.parse_args())
