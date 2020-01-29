"""\
Reads an image, increases its brightness and saves the result.
"""

import argparse
import sys

import numpy as np
import pyecvl._core.ecvl as ecvl


def inc_brightness(img, rate):
    a = np.array(img, copy=False)
    max_val = np.iinfo(a.dtype).max
    a[a > max_val - rate] = max_val
    a[a <= max_val - rate] += rate


def main(args):
    img = ecvl.ImRead(args.in_fn)
    inc_brightness(img, 10)
    ecvl.ImWrite(args.out_fn, img)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("in_fn", metavar="INPUT_PATH")
    parser.add_argument("out_fn", metavar="OUTPUT_PATH")
    main(parser.parse_args(sys.argv[1:]))
