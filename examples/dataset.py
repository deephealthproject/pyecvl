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
Reads a DeepHealth dataset.
"""

import argparse
import sys

import pyecvl.ecvl as ecvl


def main(args):
    print("reading", args.in_fn)
    d = ecvl.Dataset(args.in_fn)
    print("name:", d.name_)
    print("description:", d.description_)
    print("classes:", d.classes_)
    print("features:", d.features_)
    print("n. samples:", len(d.samples_))
    print("splits:")
    for s in d.split_:
        print(f'  "{s.split_name_}":')
        print(f'    type: {s.split_type_}')
        print(f'    n. samples: {len(s.samples_indices_)}')
        print(f'    drop last: {s.drop_last_}')
        print(f'    n. batches: {s.num_batches_}')
        print(f'    last batch: {s.last_batch_}')
        print(f'    no label: {s.no_label_}')
    print(f"current split: {d.current_split_}")
    print(f"task: {d.task_}")
    print("loading first sample image")
    print("  location:", d.samples_[0].location_)
    print("  label_path:", d.samples_[0].label_path_)
    img = d.samples_[0].LoadImage()
    out_path = "img0.png"
    print("saving first sample image as", out_path)
    ecvl.ImWrite(out_path, img)

    # check setter for completeness, but why would anyone want to do this?
    loc = ["/foo/bar"]
    d.samples_[0].location_ = loc
    assert d.samples_[0].location_ == loc
    lp = "/foo/tar"
    d.samples_[0].label_path_ = lp
    assert d.samples_[0].label_path_ == lp


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("in_fn", metavar="INPUT_PATH")
    main(parser.parse_args(sys.argv[1:]))
