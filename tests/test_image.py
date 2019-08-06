from pyecvl._core.ecvl import Image, DataType, ColorType, View_int8


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
    assert y[1, 2, 0] == 36
