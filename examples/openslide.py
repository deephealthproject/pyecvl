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
OpenSlide I/O.
"""

import argparse
import os
import sys

import pyecvl.ecvl as ecvl


def main(args):
    head, _ = os.path.splitext(os.path.basename(args.in_fn))
    levels = ecvl.OpenSlideGetLevels(args.in_fn)
    # for each level, extract a region with size = size of the last level
    dims = [0, 0] + levels[-1]  # [x, y, w, h] region to read
    print("Reading %s" % args.in_fn)
    for i in range(len(levels)):
        img = ecvl.OpenSlideRead(args.in_fn, i, dims)
        out_fn = "%s_level_%d.png" % (head, i)
        print("Writing %s" % out_fn)
        ecvl.ImWrite(out_fn, img)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("in_fn", metavar="INPUT_PATH")
    main(parser.parse_args(sys.argv[1:]))
