"""\
I/O on special formats.
"""

import argparse
import os
import sys

import pyecvl._core.ecvl as ecvl


def nifti_io(fn):
    head, ext = os.path.splitext(os.path.basename(fn))
    print("Reading %s" % fn)
    img = ecvl.NiftiRead(fn)
    ecvl.GammaContrast(img, img, 3)
    out_fn = "%s_gamma%s" % (head, ext)
    print("Saving %s" % out_fn)
    ecvl.NiftiWrite(out_fn, img)


def dicom_io(fn):
    head, ext = os.path.splitext(os.path.basename(fn))
    print("Reading %s" % fn)
    img = ecvl.DicomRead(fn)
    ecvl.ChangeColorSpace(img, img, ecvl.ColorType.GRAY)
    thresh = ecvl.OtsuThreshold(img)
    maxval = 255
    ecvl.Threshold(img, img, thresh, maxval)
    out_fn = "%s_threshold%s" % (head, ext)
    print("Saving %s" % out_fn)
    ecvl.DicomWrite(out_fn, img)


def main(args):
    nifti_io(args.nifti_fn)
    dicom_io(args.dicom_fn)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("nifti_fn", metavar="NIFTI_INPUT_PATH")
    parser.add_argument("dicom_fn", metavar="DICOM_INPUT_PATH")
    main(parser.parse_args(sys.argv[1:]))
