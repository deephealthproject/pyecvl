# Copyright (c) 2020 CRS4
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
Copy pneumothorax ground truth masks in the directory of the corresponding
images.
"""

import argparse
import os
import shutil
from os.path import splitext, join, exists


def main(args):
    shutil.copy2(join(args.gt_dir, "black.png"),
                 join(args.tr_img_dir, "black.png"))
    for root, dirs, files in os.walk(args.tr_img_dir):
        for name in files:
            head, tail = splitext(name)
            if tail != ".dcm":
                continue
            gt_name = head + ".png"
            gt_path = join(args.gt_dir, gt_name)
            if exists(gt_path):
                shutil.copy2(gt_path, join(root, gt_name))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawTextHelpFormatter
    )
    parser.add_argument("tr_img_dir", metavar="TRAINING_IMAGES_DIR",
                        help="root directory for the training imges")
    parser.add_argument("gt_dir", metavar="GROUND_TRUTH_DIR",
                        help="directory with the ground truth masks")
    main(parser.parse_args())
