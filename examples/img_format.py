# Copyright (c) 2019-2021 CRS4
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

"""\
I/O on special formats.
"""

import argparse
import os
import sys

import pyecvl.ecvl as ecvl


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
