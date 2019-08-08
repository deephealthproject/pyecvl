from pyecvl._core.ecvl import (
    Image, DataType, ColorType, View_int8, Neg, RearrangeChannels
)


def test_empty():
    img = Image()
    assert len(img.dims_) == 0
    assert img.IsEmpty()


def test_five_dims():
    dims = [1, 2, 3, 4, 5]
    img = Image(dims, DataType.uint8, "xyzoo", ColorType.none)
    assert img.dims_ == dims
    assert len(img.strides_) == len(dims)


def test_view():
    x = Image([5, 4, 3], DataType.int8, "xyc", ColorType.RGB)
    y = View_int8(x)
    y[1, 2, 0] = 36
    y[3, 3, 2] = 48
    y[4, 2, 1] = -127
    y[3, 2, 0] = -128
    Neg(x)
    assert y[1, 2, 0] == -36
    assert y[3, 3, 2] == -48
    assert y[4, 2, 1] == 127
    assert y[3, 2, 0] == -128


def test_rearrange_channels():
    img = Image([3, 4, 3, 2], DataType.int16, "cxyz", ColorType.RGB)
    img2 = Image()
    RearrangeChannels(img, img2, "xyzc")
