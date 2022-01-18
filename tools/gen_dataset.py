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
Generate a DeepHealth dataset file from a directory tree.

Assumes a directory structure where a top-level directory has subdirectories
named "training", "validation" and "test" (possibly not all present), each of
which has in turn one subdirectory for each class, containing the images for
that class. For instance:

- dataset_name
    - training
        - class_0
            - tr_0_0.png
            - tr_0_1.png
        - class_1
            - tr_1_0.png
            - tr_1_1.png
    - validation
        - class_0
            - val_0_0.png
            - val_0_1.png
        - class_1
            - val_1_0.png
            - val_1_1.png
"""

import argparse
import io
import os
import yaml

Dumper = getattr(yaml, "CDumper", "Dumper")
SPLIT_KEYS = frozenset(["training", "validation", "test"])


def dump(doc, f):
    yaml.dump(doc, f, Dumper, default_flow_style=False)


def main(args):
    name = os.path.basename(os.path.normpath(args.root))
    doc = {"name": name, "classes": set(), "images": [], "split": {}}
    for entry in os.scandir(args.root):
        if entry.name not in SPLIT_KEYS:
            continue
        if not entry.is_dir():
            continue
        doc["split"][entry.name] = []
        split = doc["split"].setdefault(entry.name, [])
        for sub_entry in os.scandir(entry.path):
            if not sub_entry.is_dir():
                continue
            doc["classes"].add(sub_entry.name)
            for sub_sub_entry in os.scandir(sub_entry.path):
                if not sub_sub_entry.is_file():
                    continue
                split.append(len(doc["images"]))
                doc["images"].append({"location": sub_sub_entry.path,
                                      "label": sub_entry.name})
    doc["classes"] = sorted(doc["classes"])
    if not args.output_file:
        args.output_file = os.path.join(args.root, "%s.yml" % name)
    with io.open(args.output_file, "wt") as f:
        dump(doc, f)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawTextHelpFormatter
    )
    parser.add_argument("root", metavar="ROOT_DIR",
                        help="top-level dataset directory")
    parser.add_argument("-o", "--output-file", metavar="STRING",
                        help="output YAML dataset file")
    main(parser.parse_args())
