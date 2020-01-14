"""\
Skin lesion classification example.
"""

import argparse
import random
import sys

import pyecvl._core.ecvl as ecvl
import pyeddl._core.eddl as eddl
import pyeddl._core.eddlT as eddlT
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

    print("Reading dataset")
    d = ecvl.DLDataset(args.in_ds, args.batch_size, size)
    x_train = eddlT.create([args.batch_size, d.n_channels_, size[0], size[1]])
    y_train = eddlT.create([args.batch_size, len(d.classes_)])
    num_samples = len(d.GetSplit())
    num_batches = num_samples // args.batch_size
    indices = list(range(args.batch_size))

    for i in range(args.epochs):
        eddl.reset_loss(net)
        s = d.GetSplit()
        random.shuffle(s)
        d.split_.training_ = s
        d.ResetCurrentBatch()
        for j in range(num_batches):
            print("Epoch %d/%d (batch %d/%d) - " %
                  (i + 1, args.epochs, j + 1, num_batches), end="", flush=True)
            d.LoadBatch(x_train, y_train)
            x_train.div_(255.0)
            tx, ty = [x_train], [y_train]
            eddl.train_batch(net, tx, ty, indices)
            eddl.print_loss(net, j)
            print()

    eddl.save(net, "isic_classification_checkpoint.bin", "bin")

    print("Evaluation")
    d.SetSplit("test")
    num_samples = len(d.GetSplit())
    num_batches = num_samples // args.batch_size
    d.ResetCurrentBatch()
    for i in range(num_batches):
        print("batch %d / %d - " % (i, num_batches), end="", flush=True)
        d.LoadBatch(x_train, y_train)
        x_train.div_(255.0)
        eddl.evaluate(net, [x_train], [y_train])


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("in_ds", metavar="INPUT_DATASET")
    parser.add_argument("--epochs", type=int, metavar="INT", default=50)
    parser.add_argument("--batch-size", type=int, metavar="INT", default=12)
    parser.add_argument("--gpu", action="store_true")
    main(parser.parse_args(sys.argv[1:]))
