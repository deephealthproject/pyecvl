"""\
Reads a DeepHealth dataset.
"""

import argparse
import sys

import pyecvl._core.ecvl as ecvl


def main(args):
    print("reading", args.in_fn)
    d = ecvl.Dataset(args.in_fn)
    print("name:", d.name_)
    print("description:", d.description_)
    print("classes:", d.classes_)
    print("features:", d.features_)
    print("n. samples:", len(d.samples_))
    print("  training:", len(d.split_.training_))
    print("  validation:", len(d.split_.validation_))
    print("  test:", len(d.split_.test_))
    print("loading first sample image")
    img = d.samples_[0].LoadImage()
    out_path = "img0.png"
    print("saving first sample image as", out_path)
    ecvl.ImWrite(out_path, img)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("in_fn", metavar="INPUT_PATH")
    main(parser.parse_args(sys.argv[1:]))
