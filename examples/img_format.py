"""\
I/O on special formats.
"""

import argparse
import os
import sys

import pyecvl._core.ecvl as ecvl


def nifti_io(fn):
    # FIXME: why isn't std::invalid_argument being converted to a Python error?
    if not os.path.isfile(fn):
        raise RuntimeError("%s does not exist or is not a file" % fn)
    head, ext = os.path.splitext(os.path.basename(fn))
    img = ecvl.Image()
    print("Reading %s" % fn)
    ecvl.ImRead(fn, img, ecvl.ImageFormat.NIFTI)
    ecvl.GammaContrast(img, img, 3)
    out_fn = "%s_gamma%s" % (head, ext)
    print("Saving %s" % out_fn)
    ecvl.ImWrite(out_fn, img, ecvl.ImageFormat.NIFTI)


def main(args):
    nifti_io(args.nifti_fn)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("nifti_fn", metavar="NIFTI_INPUT_PATH")
    main(parser.parse_args(sys.argv[1:]))
