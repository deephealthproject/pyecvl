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
Generate a smaller version of a DeepHealth dataset.

With --check, check a previous dataset reduction instead.
"""

import argparse
import io
import os
import random
import yaml

Loader = getattr(yaml, "CLoader", getattr(yaml, "Loader"))
Dumper = getattr(yaml, "CDumper", getattr(yaml, "Dumper"))


def get_splits(doc):
    return {k: [doc["images"][_]["location"] for _ in v]
            for k, v in doc["split"].items()}


def check(args):
    if not args.output_file or not args.fraction:
        raise RuntimeError(
            "in check mode, --output-file and --fraction must be set"
        )
    with io.open(args.dataset_file, "rt") as f:
        doc = yaml.load(f, Loader)
    with io.open(args.output_file, "rt") as f:
        out_doc = yaml.load(f, Loader)
    images, out_images = doc["images"], out_doc["images"]
    assert set([_["location"] for _ in out_images]).issubset(
        [_["location"] for _ in images]
    )
    if "split" in doc:
        assert "split" in out_doc
        splits, out_splits = get_splits(doc), get_splits(out_doc)
        assert splits.keys() == out_splits.keys()
        for k, out_v in out_splits.items():
            v = splits[k]
            assert set(out_v).issubset(v)
            assert abs(len(out_v) - args.fraction * len(v)) <= 1
    else:
        assert abs(len(out_images) - args.fraction * len(images)) <= 1


def dump(doc, f):
    yaml.dump(doc, f, Dumper, default_flow_style=False)


def reduce_dataset(args):
    with io.open(args.dataset_file, "rt") as f:
        doc = yaml.load(f, Loader)
    images = doc["images"]
    try:
        split = doc["split"]
    except KeyError:
        n_out = round(args.fraction * len(images))
        doc["images"] = images[:n_out]
    else:
        training = split.get("training", [])
        validation = split.get("validation", [])
        test = split.get("test", [])
        n_tr = max(round(args.fraction * len(training)), 1)
        n_val = max(round(args.fraction * len(validation)), 1)
        n_test = max(round(args.fraction * len(test)), 1)
        out_tr = [images[_] for _ in random.sample(training, n_tr)]
        out_val = [images[_] for _ in random.sample(validation, n_val)]
        out_test = [images[_] for _ in random.sample(test, n_test)]
        doc["images"] = out_tr + out_val + out_test
        doc["split"]["training"] = list(range(n_tr))
        doc["split"]["validation"] = list(range(n_tr, n_tr + n_val))
        doc["split"]["test"] = list(range(n_tr + n_val, n_tr + n_val + n_test))
        doc["split"] = {k: v for k, v in doc["split"].items() if v}
    if not args.output_file:
        head, tail = os.path.splitext(args.dataset_file)
        args.output_file = "%s_small%s" % (head, tail)
    with io.open(args.output_file, "wt") as f:
        dump(doc, f)


def main(args):
    if args.check:
        check(args)
    else:
        reduce_dataset(args)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("dataset_file", metavar="DATASET_FILE",
                        help="YAML dataset file")
    parser.add_argument("-f", "--fraction", metavar="FLOAT", type=float,
                        default=.1, help="fraction of the dataset to extract")
    parser.add_argument("-o", "--output-file", metavar="STRING",
                        help="output YAML dataset file")
    parser.add_argument("-c", "--check", action="store_true",
                        help="check a previous dataset reduction")
    main(parser.parse_args())
