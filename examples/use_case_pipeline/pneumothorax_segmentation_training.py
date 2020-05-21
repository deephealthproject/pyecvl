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
Pneumothorax segmentation training example.

More information and checkpoints available at
https://github.com/deephealthproject/use_case_pipeline
"""

import argparse
import math
import os
import random

import numpy as np
import pyeddl.eddl as eddl
import pyeddl.eddlT as eddlT
import pyecvl.ecvl as ecvl

import utils
from models import SegNetBN


def PneumothoraxLoadBatch(d, black_indices, m_i, b_i):
    mask_indices = d.GetSplit()
    len_mask_indices = len(mask_indices)
    bs = d.batch_size_
    names = []
    images = []
    labels = []

    if d.current_split_ == ecvl.SplitType.training:
        index = 0
    elif d.current_split_ == ecvl.SplitType.validation:
        index = 1
    else:
        index = 2

    start = d.current_batch_[index] * bs
    d.current_batch_ = [elem + 1 if i == index else elem for i, elem in
                        enumerate(d.current_batch_)]

    expr = True
    for i in range(start, start + bs):
        if d.current_split_ == ecvl.SplitType.training:
            # in training, check if you can take
            # other black ground truth images..
            if len_mask_indices * 1.25 - i > len_mask_indices - m_i:
                expr = random.random() >= 0.2 and m_i < len_mask_indices
            # ..otherwise, you have to take a ground truth with mask
        else:
            # in validation, first take all the samples with the ground
            # truth with mask and then all those with the black ground truth.
            expr = m_i < len_mask_indices

        if expr:
            index = mask_indices[m_i]
            m_i += 1
        else:
            index = black_indices[b_i]
            b_i += 1
        # insert the original name of images and ground truth in case
        # you want to save predictions during validation
        elem = d.samples_[index]
        names.append(elem.location_[0])
        names.append(elem.label_path_)

        # Read the image
        img = elem.LoadImage(d.ctype_, False)

        # Read the ground truth
        gt = elem.LoadImage(d.ctype_gt_, True)

        # Apply chain of augmentations to sample image
        # and corresponding ground truth
        d.augs_.Apply(d.current_split_, img, gt)

        # Copy image into tensor (images)
        images.append(ecvl.ImageToTensor(img))

        # Copy label into tensor (labels)
        labels.append(ecvl.ImageToTensor(gt))

    return d, images, labels, names, m_i, b_i


def fill_tensors(images, labels, x, y):
    x_np = np.array(x, copy=False)
    y_np = np.array(y, copy=False)

    for i, (img, lab) in enumerate(zip(images, labels)):
        img_np = np.array(img, copy=False)
        lab_np = np.array(lab, copy=False)
        x_np[i, ...] = img_np
        y_np[i, ...] = lab_np

    return x, y


def main(args):
    num_classes = 1
    size = [512, 512]  # size of images
    thresh = 0.5
    best_dice = -1

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
        eddl.CS_GPU([1], mem='low_mem') if args.gpu else eddl.CS_CPU()
    )
    eddl.summary(net)
    eddl.setlogfile(net, "pneumothorax_segmentation_training")

    if args.ckpts and os.path.exists(args.ckpts):
        print("Loading checkpoints '{}'".format(args.ckpts))
        eddl.load(net, args.ckpts, 'bin')

    training_augs = ecvl.SequentialAugmentationContainer([
        ecvl.AugResizeDim(size),
        ecvl.AugMirror(0.5),
        ecvl.AugRotate([-10, 10]),
        ecvl.AugBrightness([0, 30]),
        ecvl.AugGammaContrast([0, 3]),
    ])
    validation_augs = ecvl.SequentialAugmentationContainer([
        ecvl.AugResizeDim(size)
    ])
    dataset_augs = ecvl.DatasetAugmentations([
        training_augs, validation_augs, None
    ])

    print("Reading dataset")
    d = ecvl.DLDataset(args.in_ds, args.batch_size, dataset_augs,
                       ecvl.ColorType.GRAY)
    # Prepare tensors which store batch
    x = eddlT.create([args.batch_size, d.n_channels_, size[0], size[1]])
    y = eddlT.create([args.batch_size, d.n_channels_gt_, size[0], size[1]])

    # Retrieve indices of images with a black ground truth
    # which are not include in a split
    train_split = d.GetSplit(ecvl.SplitType.training)
    val_split = d.GetSplit(ecvl.SplitType.validation)
    test_split = d.GetSplit(ecvl.SplitType.test)
    all_split = set(train_split + val_split + test_split)

    images_list = set(range(len(d.samples_)))

    # Obtain images with black ground truth
    black_images = images_list - all_split

    # Add a 25% of training samples with black ground truth.
    num_samples_train = math.floor(len(train_split) * 1.25)
    num_batches_train = num_samples_train // args.batch_size

    # Add a 25% of validation samples with black ground truth.
    num_samples_validation = math.floor(len(val_split) * 1.25)
    num_batches_validation = num_samples_validation // args.batch_size

    black_images = list(black_images)
    black_training = black_images[
                     0: -(num_samples_validation - len(val_split))]
    black_validation = black_images[
                       -(num_samples_validation - len(val_split)):]
    indices = list(range(args.batch_size))

    evaluator = utils.Evaluator()
    print("Starting training")
    for e in range(args.epochs):
        print("Epoch {:d}/{:d} - Training".format(e + 1, args.epochs),
              flush=True)
        d.SetSplit(ecvl.SplitType.training)
        eddl.reset_loss(net)
        s = d.GetSplit()
        random.shuffle(s)
        d.split_.training_ = s
        random.shuffle(black_training)

        d.ResetAllBatches()
        # Indices to track mask and black vector in PneumothoraxLoadBatch
        m_i = 0
        b_i = 0
        for i, b in enumerate(range(num_batches_train)):
            d, images, labels, _, m_i, b_i = PneumothoraxLoadBatch(
                d, black_training, m_i, b_i)
            x, y = fill_tensors(images, labels, x, y)
            x.div_(255.0)
            y.div_(255.0)
            eddl.train_batch(net, [x], [y], indices)
            if i % args.log_interval == 0:
                print("Epoch {:d}/{:d} (batch {:d}/{:d}) - ".format(
                    e + 1, args.epochs, b + 1, num_batches_train
                ), end="", flush=True)
                eddl.print_loss(net, b)
                print()

        d.SetSplit(ecvl.SplitType.validation)
        evaluator.ResetEval()
        print("Epoch %d/%d - Evaluation" % (e + 1, args.epochs), flush=True)
        m_i = 0
        b_i = 0
        for b in range(num_batches_validation):
            n = 0
            print("Epoch {:d}/{:d} (batch {:d}/{:d}) ".format(
                e + 1, args.epochs, b + 1, num_batches_validation
            ), end="", flush=True)
            d, images, labels, names, m_i, b_i = PneumothoraxLoadBatch(
                d, black_validation, m_i, b_i)
            x, y = fill_tensors(images, labels, x, y)
            x.div_(255.0)
            y.div_(255.0)
            eddl.forward(net, [x])
            output = eddl.getTensor(out_sigm)

            # Compute Dice metric and optionally save the output images
            for k in range(args.batch_size):
                pred = eddlT.select(output, k)
                gt = eddlT.select(y, k)
                pred_np = np.array(pred, copy=False)
                gt_np = np.array(gt, copy=False)
                # DiceCoefficient modifies image as a side effect
                dice = evaluator.DiceCoefficient(pred_np, gt_np, thresh=thresh)
                print("- Dice: {:.6f} ".format(dice), end="", flush=True)

                if args.out_dir:
                    # Save original image fused together with prediction and
                    # ground truth
                    pred_np *= 255
                    pred_ecvl = ecvl.TensorToImage(pred)
                    pred_ecvl.colortype_ = ecvl.ColorType.GRAY
                    pred_ecvl.channels_ = "xyc"
                    ecvl.ResizeDim(pred_ecvl, pred_ecvl, (1024, 1024),
                                   ecvl.InterpolationType.nearest)

                    filename_gt = names[n + 1]
                    gt_ecvl = ecvl.ImRead(filename_gt,
                                          ecvl.ImReadMode.GRAYSCALE)

                    filename = names[n]

                    # Image as BGR
                    img_ecvl = ecvl.ImRead(filename)
                    ecvl.Stack([img_ecvl, img_ecvl, img_ecvl], img_ecvl)
                    img_ecvl.channels_ = "xyc"
                    img_ecvl.colortype_ = ecvl.ColorType.BGR
                    image_np = np.array(img_ecvl, copy=False)
                    pred_np = np.array(pred_ecvl, copy=False)
                    gt_np = np.array(gt_ecvl, copy=False)

                    pred_np = pred_np.squeeze()
                    gt_np = gt_np.squeeze()
                    # Prediction summed in R channel
                    image_np[:, :, -1] = np.where(pred_np == 255, pred_np,
                                                  image_np[:, :, -1])
                    # Ground truth summed in G channel
                    image_np[:, :, 1] = np.where(gt_np == 255, gt_np,
                                                 image_np[:, :, 1])

                    n += 2
                    head, tail = os.path.splitext(os.path.basename(filename))
                    bname = "{}.png".format(head)
                    filepath = os.path.join(args.out_dir, bname)
                    ecvl.ImWrite(filepath, img_ecvl)

            print()

        mean_dice = evaluator.MeanMetric()
        if mean_dice > best_dice:
            print("Saving weights")
            eddl.save(net, "pneumothorax_segnetBN_adam_lr_0.0001_"
                           "loss_ce_size_512_{}.bin".format(e + 1), "bin")
            best_dice = mean_dice
        print("Mean Dice Coefficient: {:.6g}".format(mean_dice))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("in_ds", metavar="INPUT_DATASET")
    parser.add_argument("--epochs", type=int, metavar="INT", default=20)
    parser.add_argument("--batch-size", type=int, metavar="INT", default=2)
    parser.add_argument("--log-interval", type=int, metavar="INT", default=100)
    parser.add_argument("--gpu", action="store_true")
    parser.add_argument("--out-dir", metavar="DIR",
                        help="if set, save images in this directory")
    parser.add_argument("--ckpts", type=str)
    main(parser.parse_args())
