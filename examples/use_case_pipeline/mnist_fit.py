"""\
MNIST fit.
"""

import argparse
import sys

import pyecvl._core.ecvl as ecvl
import pyeddl._core.eddl as eddl
from models import LeNet


def main(args):
    num_classes = 10
    size = [28, 28]  # size of images
    ctype = ecvl.ColorType.GRAY

    in_ = eddl.Input([1, size[0], size[1]])
    out = LeNet(in_, num_classes)
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
    d = ecvl.Dataset(args.in_ds)
    x_train, y_train = ecvl.TrainingToTensor(d, size, ctype)
    x_train.div_(255.0)
    eddl.fit(net, [x_train], [y_train], args.batch_size, args.epochs)
    eddl.save(net, "mnist_checkpoint.bin", "bin")

    x_test, y_test = ecvl.TestToTensor(d, size, ctype)
    x_test.div_(255.0)
    eddl.evaluate(net, [x_test], [y_test])


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("in_ds", metavar="INPUT_DATASET")
    parser.add_argument("--epochs", type=int, metavar="INT", default=5)
    parser.add_argument("--batch-size", type=int, metavar="INT", default=64)
    parser.add_argument("--gpu", action="store_true")
    main(parser.parse_args(sys.argv[1:]))
