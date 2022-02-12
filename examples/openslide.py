# Copyright (c) 2019-2022 CRS4
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
    if not ecvl.ECVL_WITH_OPENSLIDE:
        print("No OpenSlide support - quitting")
        sys.exit(0)
    head, _ = os.path.splitext(os.path.basename(args.in_fn))
    print("Reading %s" % args.in_fn)
    with ecvl.OpenSlideImage(args.in_fn) as os_img:
        n_levels = os_img.GetLevelCount()
        print(f"Number of levels: {n_levels}")
        levels = os_img.GetLevelsDimensions()
        # for each level, extract a region with size = size of the last level
        dims = [0, 0] + levels[-1]  # [x, y, w, h] region to read
        img = None
        for i in range(len(levels)):
            img = os_img.ReadRegion(i, dims)
            os_img.GetProperties(img)
            out_fn = "%s_level_%d.png" % (head, i)
            print("Writing %s" % out_fn)
            ecvl.ImWrite(out_fn, img)
    mpp_x = img.GetMeta("openslide.mpp-x")
    print(f"mpp-x: {mpp_x.GetStr()}")
    metadata_dump_fn = f"{head}_metadata.txt"
    print(f"Dumping metadata to {metadata_dump_fn}")
    with open(metadata_dump_fn, "wt") as dump_f:
        for k, v in img.meta_.items():
            dump_f.write(f"{k}: {v.GetStr()}\n")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("in_fn", metavar="INPUT_PATH")
    main(parser.parse_args(sys.argv[1:]))
