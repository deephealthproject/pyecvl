"""\
OpenSlide I/O.
"""

import argparse
import os
import sys

import pyecvl._core.ecvl as ecvl


def main(args):
    # FIXME: why isn't std::invalid_argument being converted to a Python error?
    if not os.path.isfile(args.in_fn):
        raise RuntimeError("%s does not exist or is not a file" % args.in_fn)
    head, _ = os.path.splitext(os.path.basename(args.in_fn))
    levels = ecvl.OpenSlideGetLevels(args.in_fn)
    # for each level, extract a region with size = size of the last level
    dims = [0, 0] + levels[-1]  # [x, y, w, h] region to read
    img = ecvl.Image()
    print("Reading %s" % args.in_fn)
    for i in range(len(levels)):
        ecvl.OpenSlideRead(args.in_fn, img, i, dims)
        out_fn = "%s_level_%d.png" % (head, i)
        print("Writing %s" % out_fn)
        ecvl.ImWrite(out_fn, img)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("in_fn", metavar="INPUT_PATH")
    main(parser.parse_args(sys.argv[1:]))
