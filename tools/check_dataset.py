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
Perform consistency checks on a DeepHealth dataset.
"""

import argparse
import io
import os
import yaml

Loader = getattr(yaml, "CLoader", "Loader")
SPLIT_KEYS = frozenset(["training", "validation", "test"])


def check_images(images, ds_dir):
    for entry in images:
        # entry can be a string or a dict with a "location" key
        try:
            location = entry["location"]
        except TypeError:
            location = entry
        location = os.path.join(ds_dir, location)
        if not os.path.isfile(location):
            raise RuntimeError("%s does not exist" % location)


def main(args):
    print("reading dataset")
    with io.open(args.dataset_file, "rt") as f:
        doc = yaml.load(f, Loader)
    assert "images" in doc
    print("checking images")
    check_images(doc["images"], os.path.dirname(args.dataset_file))
    try:
        split = doc["split"]
    except KeyError:
        return
    print("checking split")
    assert set(split).issubset(SPLIT_KEYS)
    for k, v in split.items():
        for i in v:
            assert 0 <= i < len(doc["images"])


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("dataset_file", metavar="DATASET_FILE",
                        help="YAML dataset file")
    main(parser.parse_args())
