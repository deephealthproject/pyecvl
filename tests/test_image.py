from pyecvl._core.ecvl import Image


def test_empty():
    img = Image()
    assert len(img.dims_) == 0
    assert img.IsEmpty()
