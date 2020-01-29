"""\
ECVL-EDDL interaction.
"""

import argparse
import sys

import pyecvl._core.ecvl as ecvl
import pyeddl._core.eddlT as eddlT


def main(args):
    img = ecvl.ImRead(args.in_img)
    print("Executing ImageToTensor")
    t = ecvl.ImageToTensor(img)
    eddlT.div_(t, 128)
    print("Executing TensorToImage")
    img = ecvl.TensorToImage(t)
    print("Executing TensorToView")
    ecvl.TensorToView(t)

    batch_size = 64
    print("Creating a DLDataset")
    d = ecvl.DLDataset(args.in_ds, batch_size, [28, 56], ecvl.ColorType.GRAY)
    print("Create x_train and y_train")
    x_train = eddlT.create(
        [batch_size, d.n_channels_, d.resize_dims_[0], d.resize_dims_[1]]
    )
    y_train = eddlT.create([batch_size, len(d.classes_)])

    # Load a batch of d.batch_size_ images into x_train and corresponding
    # labels in y_train. Images are resized to the dimensions specified in size
    print("Executing LoadBatch")
    d.LoadBatch(x_train, y_train)

    # Load test images in x_test and corresponding labels in y_test
    print("Executing TestToTensor")
    x_test, y_test = ecvl.TestToTensor(d, d.resize_dims_, ecvl.ColorType.GRAY)
    print("x_test info:")
    eddlT.info(x_test)
    print("y_test info:")
    eddlT.info(y_test)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("in_img", metavar="INPUT_IMAGE")
    parser.add_argument("in_ds", metavar="INPUT_DATASET")
    main(parser.parse_args(sys.argv[1:]))
