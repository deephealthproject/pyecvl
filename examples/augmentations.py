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
Reads an image, applies augmentations and writes results.
"""

import argparse
import os
import sys

import pyecvl.ecvl as ecvl


def main(args):
    if not ecvl.ECVL_EDDL:
        print("No EDDL support - quitting")
        sys.exit(0)
    head, ext = os.path.splitext(os.path.basename(args.in_fn))
    img = ecvl.ImRead(args.in_fn)
    c = ecvl.SequentialAugmentationContainer([ecvl.AugFlip(0.5)])
    da = ecvl.DatasetAugmentations([c, None, None])
    # some output images should be flipped
    for i in range(10):
        da.Apply(ecvl.SplitType.training, img)
        out_fn = "%s_flip_%d%s" % (head, i, ext)
        print("writing", out_fn)
        ecvl.ImWrite(out_fn, img)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("in_fn", metavar="INPUT_PATH")
    main(parser.parse_args(sys.argv[1:]))
