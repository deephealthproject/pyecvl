"""\
Performs image processing on an input image.
"""

import argparse
import os
import sys

import pyecvl._core.ecvl as ecvl


def main(args):
    # FIXME: why isn't std::invalid_argument being converted to a Python error?
    if not os.path.isfile(args.in_fn):
        raise RuntimeError("%s does not exist or is not a file" % args.in_fn)
    head, ext = os.path.splitext(os.path.basename(args.in_fn))
    img, tmp = ecvl.Image(), ecvl.Image()
    ecvl.ImRead(args.in_fn, img)
    ecvl.Flip2D(img, tmp)
    ecvl.ImWrite("%s_flipped%s" % (head, ext), tmp)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("in_fn", metavar="INPUT_PATH")
    main(parser.parse_args(sys.argv[1:]))
