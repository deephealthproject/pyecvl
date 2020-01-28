import io
import pytest
import pyecvl._core.ecvl as ecvl


DATASET = """\
name: Foo
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
split:
  training:
  - 0
  - 1
  test:
  - 2
"""


def test_load(tmp_path):
    fn = str(tmp_path / "foo.yml")
    with io.open(fn, "wt") as f:
        f.write(DATASET)
    d = ecvl.Dataset(fn)
    assert d.name_ == "Foo"
    assert d.classes_ == ["0", "1", "2"]
    assert len(d.samples_) == 3
    with pytest.raises(RuntimeError):
        d.samples_[0].LoadImage()


def test_load_nonexistent():
    with pytest.raises(RuntimeError):
        ecvl.Dataset("/not/existing.yml")
