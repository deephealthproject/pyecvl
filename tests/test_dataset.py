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

import io
import os
import pytest

import pyecvl._core.ecvl as ecvl_core
import pyecvl.ecvl as ecvl_py


DATASET = """\
name: Foo
description: FooDesc
classes:
- '0'
- '1'
- '2'
images:
- location: foo_0.png
  label: 2
- location: foo_1.png
  label: 0
- location: foo_2.png
  label: 1
- location: foo_3.png
  label: 1
split:
  training:
  - 0
  - 1
  test:
  - 2
  validation:
  - 3
"""


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_split(ecvl, tmp_path):
    s = ecvl.Split()
    n_samples = 7
    samples_indices = list(range(n_samples))
    for name in "test", "training", "validation":
        s = ecvl.Split(name, samples_indices)
        assert s.split_name_ == name
        assert s.split_type_ == getattr(ecvl.SplitType, name)
        assert s.samples_indices_ == samples_indices
    s = ecvl.Split("foo", samples_indices)
    assert not s.drop_last_
    batch_size = 3
    s.SetNumBatches(batch_size)
    s.SetLastBatch(batch_size)
    assert s.num_batches_ == 3
    assert s.last_batch_ == 1
    s.drop_last_ = True
    s.SetNumBatches(batch_size)
    s.SetLastBatch(batch_size)
    assert s.num_batches_ == 2
    assert s.last_batch_ == batch_size
    n_samples = 9
    samples_indices = list(range(n_samples))
    s = ecvl.Split("bar", samples_indices)
    s.SetNumBatches(batch_size)
    s.SetLastBatch(batch_size)
    assert s.num_batches_ == 3
    assert s.last_batch_ == 3
    s.drop_last_ = True
    s.SetNumBatches(batch_size)
    s.SetLastBatch(batch_size)
    assert s.num_batches_ == 3
    assert s.last_batch_ == batch_size
    s = ecvl.Split("tar", samples_indices, drop_last=True, no_label=True)
    assert s.drop_last_
    assert s.no_label_


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_load(ecvl, tmp_path):
    fn = str(tmp_path / "foo.yml")
    with io.open(fn, "wt") as f:
        f.write(DATASET)
    d = ecvl.Dataset(fn)
    assert d.name_ == "Foo"
    assert d.description_ == "FooDesc"
    assert d.classes_ == ["0", "1", "2"]
    assert not d.features_
    assert len(d.samples_) == 4
    with pytest.raises(RuntimeError):
        d.samples_[0].LoadImage()
    locations = [os.path.basename(_.location_[0]) for _ in d.samples_]
    assert locations == ["foo_0.png", "foo_1.png", "foo_2.png", "foo_3.png"]
    assert d.task_ == ecvl.Task.classification
    # check splits
    split_by_name = {_.split_name_: _ for _ in d.split_}
    assert set(split_by_name) == {"training", "test", "validation"}
    assert split_by_name["training"].split_type_ == ecvl.SplitType.training
    assert set(split_by_name["training"].samples_indices_) == {0, 1}
    assert set(d.GetSplit("training")) == {0, 1}
    assert set(d.GetSplit(ecvl.SplitType.training)) == {0, 1}
    assert split_by_name["test"].split_type_ == ecvl.SplitType.test
    assert set(split_by_name["test"].samples_indices_) == {2}
    assert set(d.GetSplit("test")) == {2}
    assert set(d.GetSplit(ecvl.SplitType.test)) == {2}
    assert split_by_name["validation"].split_type_ == ecvl.SplitType.validation
    assert set(split_by_name["validation"].samples_indices_) == {3}
    assert set(d.GetSplit("validation")) == {3}
    assert set(d.GetSplit(ecvl.SplitType.validation)) == {3}
    # set / get current split
    split_by_type = {_.split_type_: _ for _ in d.split_}
    for t in "training", "test", "validation":
        d.SetSplit(t)
        assert d.GetSplit(-1) == split_by_name[t].samples_indices_
    for t in ecvl.SplitType.training, ecvl.SplitType.test, ecvl.SplitType.validation:
        d.SetSplit(t)
        assert d.GetSplit(-1) == split_by_type[t].samples_indices_
    for i, s in enumerate(d.split_):
        d.SetSplit(i)
        assert d.GetSplit(-1) == d.split_[i].samples_indices_
        assert d.GetSplit() == d.split_[i].samples_indices_


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_load_nonexistent(ecvl):
    with pytest.raises(RuntimeError):
        ecvl.Dataset("/not/existing.yml")
