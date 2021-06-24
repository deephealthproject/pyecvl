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

import numpy as np
import pytest

import pyecvl._core.ecvl as ecvl_core
import pyecvl.ecvl as ecvl_py


def _empty_img(ecvl):
    if ecvl is ecvl_core:
        return ecvl.Image()
    return ecvl.Image.empty()


def _img_fromarray(ecvl, array, channels, colortype, spacings=None):
    if spacings is None:
        spacings = []
    if ecvl is ecvl_core:
        return ecvl.Image(array, channels, colortype, spacings)
    return ecvl.Image.fromarray(array, channels, colortype, spacings)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_empty(ecvl):
    img = _empty_img(ecvl)
    assert len(img.dims_) == 0
    assert img.IsEmpty()


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_copy(ecvl):
    dims, dtype = [2, 4, 3], ecvl.DataType.int8
    ch, ctype = "xyc", ecvl.ColorType.RGB
    x = ecvl.Image(dims, dtype, ch, ctype)
    a = np.array(x, copy=False)
    a.fill(3)
    y = x.copy()
    assert y.dims_ == dims
    assert y.elemtype_ == dtype
    assert y.channels_ == ch
    assert y.colortype_ == ctype
    b = np.array(y, copy=False)
    assert (b == 3).all()
    # ecvl_core can also use copy constructor binding
    if ecvl is ecvl_core:
        y = ecvl.Image(x)
        assert y.dims_ == dims
        assert y.elemtype_ == dtype
        assert y.channels_ == ch
        assert y.colortype_ == ctype
        b = np.array(y, copy=False)
        assert (b == 3).all()


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_five_dims(ecvl):
    dims = [1, 2, 3, 4, 5]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyzoo", ecvl.ColorType.none)
    assert img.dims_ == dims
    assert len(img.strides_) == len(dims)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_height_width_channels(ecvl):
    img = ecvl.Image([3, 10, 8], ecvl.DataType.int8, "cxy", ecvl.ColorType.BGR)
    assert img.Channels() == 3
    assert img.Width() == 10
    assert img.Height() == 8


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_extra_args(ecvl):
    dims = [1, 2, 3, 4, 5]
    spacings = [1.1, 1.1]
    dev = ecvl.Device.CPU
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyzoo", ecvl.ColorType.none,
                     spacings, dev)
    assert img.dims_ == dims
    assert len(img.strides_) == len(dims)
    assert img.spacings_ == pytest.approx(spacings)
    assert img.dev_ == dev
    img.To(ecvl.Device.CPU)
    assert img.dev_ == dev


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_view(ecvl):
    x = ecvl.Image([5, 4, 3], ecvl.DataType.int8, "xyc", ecvl.ColorType.RGB)
    assert x.Channels() == 3
    assert x.IsOwner()
    y = ecvl.View_int8(x)
    assert not y.IsOwner()
    y[1, 2, 0] = 36
    y[3, 3, 2] = 48
    y[4, 2, 1] = -127
    y[3, 2, 0] = -128
    dst = _empty_img(ecvl)
    ecvl.Neg(x, dst, ecvl.DataType.int8, False)
    dst_view = ecvl.View_int8(dst)
    assert dst_view[1, 2, 0] == -36
    assert dst_view[3, 3, 2] == -48
    assert dst_view[4, 2, 1] == 127
    assert dst_view[3, 2, 0] == -128


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_rearrange_channels(ecvl):
    S = [3, 4, 3, 2]
    img = ecvl.Image(S, ecvl.DataType.int16, "cxyz", ecvl.ColorType.RGB)
    view = ecvl.View_int16(img)
    for i in range(S[0]):
        for j in range(S[1]):
            for k in range(S[2]):
                for l in range(S[3]):  # noqa
                    view[i, j, k, l] = l + k * S[3] + j * S[2] * S[3] + i * S[1] * S[2] * S[3]
    img2 = _empty_img(ecvl)
    ecvl.RearrangeChannels(img, img2, "xyzc")
    view2 = ecvl.View_int16(img2)
    assert view2[2, 0, 1, 0] == view[0, 2, 0, 1]
    assert view2[3, 1, 1, 2] == view[2, 3, 1, 1]
    assert view2[0, 2, 0, 1] == view[1, 0, 2, 0]
    assert view2[1, 2, 0, 1] == view[1, 1, 2, 0]


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_numpy(ecvl):
    shape = [2, 3, 4]
    img = ecvl.Image(shape, ecvl.DataType.int16, "xyc", ecvl.ColorType.none)
    view = ecvl.View_int16(img)
    a = np.array(img, copy=False)
    assert list(a.shape) == shape
    assert list(a.strides) == img.strides_
    assert a.dtype == np.int16
    for i in range(shape[0]):
        for j in range(shape[1]):
            for k in range(shape[2]):
                assert a[i, j, k] == view[i, j, k]
    a.flat = 42
    b = np.array(img, copy=True)
    assert np.array_equal(a + img, a + b)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_numpy_types(ecvl):
    shape, channels, color_type = [2, 3], "xy", ecvl.ColorType.none
    for dt_name in ("int8", "int16", "int32", "int64",
                    "float32", "float64", "uint8", "uint16"):
        np_dt = getattr(np, dt_name)
        dt = getattr(ecvl.DataType, dt_name)
        img = ecvl.Image(shape, dt, channels, color_type)
        a = np.array(img, copy=False)
        assert a.dtype == np_dt


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_image_from_array(ecvl):
    channels, color_type = "xy", ecvl.ColorType.none
    for dt_name in ("int8", "int16", "int32", "int64",
                    "float32", "float64", "uint8", "uint16"):
        np_dt = getattr(np, dt_name)
        dt = getattr(ecvl.DataType, dt_name)
        a = np.arange(12).reshape(3, 4).astype(np_dt)
        b = np.asfortranarray(a)
        img = _img_fromarray(ecvl, b, channels, color_type)
        assert img.elemtype_ == dt
        assert img.dims_ == list(b.shape)
        assert img.strides_ == list(b.strides)
        # check construction from c-style array
        img = _img_fromarray(ecvl, a, channels, color_type)
        assert img.elemtype_ == dt
        assert img.dims_ == list(a.shape)
        assert img.strides_ == list(b.strides)
    a = np.arange(12).reshape(3, 4).astype(np.int16)
    b = np.asfortranarray(a)
    img = _img_fromarray(ecvl, b, channels, color_type)
    view = ecvl.View_int16(img)
    for i in range(3):
        for j in range(4):
            assert view[i, j] == b[i, j]
    # check construction from c-style array
    img = _img_fromarray(ecvl, a, channels, color_type)
    view = ecvl.View_int16(img)
    for i in range(3):
        for j in range(4):
            assert view[i, j] == a[i, j]


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_add(ecvl):
    x = ecvl.Image([2, 4, 3], ecvl.DataType.int8, "xyc", ecvl.ColorType.RGB)
    y = ecvl.Image([2, 4, 3], ecvl.DataType.int8, "xyc", ecvl.ColorType.RGB)
    a = np.array(x, copy=False)
    b = np.array(y, copy=False)
    a.fill(10)
    b.fill(3)
    x.Add(y)
    assert (a == 13).all()
    a.fill(10)
    x += y
    assert (a == 13).all()
    a.fill(10)
    b.fill(118)
    x.Add(y)
    assert (a == 127).all()
    a.fill(10)
    x.Add(y, saturate=False)
    assert (a == -128).all()


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_sub(ecvl):
    x = ecvl.Image([2, 4, 3], ecvl.DataType.int8, "xyc", ecvl.ColorType.RGB)
    y = ecvl.Image([2, 4, 3], ecvl.DataType.int8, "xyc", ecvl.ColorType.RGB)
    a = np.array(x, copy=False)
    b = np.array(y, copy=False)
    a.fill(-10)
    b.fill(3)
    x.Sub(y)
    assert (a == -13).all()
    a.fill(-10)
    x -= y
    assert (a == -13).all()
    a.fill(-10)
    b.fill(119)
    x.Sub(y)
    assert (a == -128).all()
    a.fill(-10)
    x.Sub(y, saturate=False)
    assert (a == 127).all()


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_mul(ecvl):
    x = ecvl.Image([2, 4, 3], ecvl.DataType.int8, "xyc", ecvl.ColorType.RGB)
    y = ecvl.Image([2, 4, 3], ecvl.DataType.int8, "xyc", ecvl.ColorType.RGB)
    a = np.array(x, copy=False)
    b = np.array(y, copy=False)
    a.fill(16)
    b.fill(3)
    x.Mul(y)
    assert (a == 48).all()
    a.fill(16)
    x *= y
    assert (a == 48).all()
    a.fill(16)
    b.fill(8)
    x.Mul(y)
    assert (a == 127).all()
    a.fill(16)
    x.Mul(y, saturate=False)
    assert (a == -128).all()


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_div(ecvl):
    x = ecvl.Image([2, 4, 3], ecvl.DataType.int8, "xyc", ecvl.ColorType.RGB)
    y = ecvl.Image([2, 4, 3], ecvl.DataType.int8, "xyc", ecvl.ColorType.RGB)
    a = np.array(x, copy=False)
    b = np.array(y, copy=False)
    a.fill(11)
    b.fill(2)
    x.Div(y)
    assert (a == 5).all()


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_copy_image(ecvl):
    dims, dtype = [2, 4, 3], ecvl.DataType.int8
    ch, ctype = "xyc", ecvl.ColorType.RGB
    x = ecvl.Image(dims, dtype, ch, ctype)
    a = np.array(x, copy=False)
    a.fill(3)
    # without dtype arg
    y = _empty_img(ecvl)
    ecvl.CopyImage(x, y)
    assert y.dims_ == dims
    assert y.elemtype_ == dtype
    assert y.channels_ == ch
    assert y.colortype_ == ctype
    b = np.array(y, copy=False)
    assert (b == 3).all()
    # with dtype arg
    new_dtype = ecvl.DataType.float32
    y = _empty_img(ecvl)
    ecvl.CopyImage(x, y, new_dtype)
    assert y.dims_ == dims
    assert y.elemtype_ == new_dtype
    assert y.channels_ == ch
    assert y.colortype_ == ctype
    b = np.array(y, copy=False)
    assert (b == 3).all()


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_shallow_copy_image(ecvl):
    dims, dtype = [2, 4, 3], ecvl.DataType.int8
    ch, ctype = "xyc", ecvl.ColorType.RGB
    x = ecvl.Image(dims, dtype, ch, ctype)
    a = np.array(x, copy=False)
    a.fill(3)
    y = _empty_img(ecvl)
    ecvl.ShallowCopyImage(x, y)
    assert y.dims_ == dims
    assert y.elemtype_ == dtype
    assert y.channels_ == ch
    assert y.colortype_ == ctype
    b = np.array(y, copy=False)
    assert (b == 3).all()
    b.fill(4)
    assert (a == 4).all()
    assert x.IsOwner()
    assert not y.IsOwner()


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_ConvertTo(ecvl):
    x = ecvl.Image([2, 4, 3], ecvl.DataType.uint8, "xyc", ecvl.ColorType.RGB)
    y = _empty_img(ecvl)
    a = np.array(x, copy=False)
    a.fill(128)
    # saturate = False
    ecvl.ConvertTo(x, y, ecvl.DataType.int8, False)
    assert y.elemtype_ == ecvl.DataType.int8
    b = np.array(y, copy=False)
    assert (b == -128).all()
    # saturate = True
    ecvl.ConvertTo(x, y, ecvl.DataType.int8, True)
    assert y.elemtype_ == ecvl.DataType.int8
    b = np.array(y, copy=False)
    assert (b == 127).all()
    # saturate = True by default
    ecvl.ConvertTo(x, y, ecvl.DataType.int8)
    assert y.elemtype_ == ecvl.DataType.int8
    b = np.array(y, copy=False)
    assert (b == 127).all()


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_ConvertTo_method(ecvl):
    # saturate = False
    x = ecvl.Image([2, 4, 3], ecvl.DataType.uint8, "xyc", ecvl.ColorType.RGB)
    a = np.array(x, copy=False)
    a.fill(128)
    x.ConvertTo(ecvl.DataType.int8, False)
    assert x.elemtype_ == ecvl.DataType.int8
    a = np.array(x, copy=False)
    assert (a == -128).all()
    # saturate = True
    x = ecvl.Image([2, 4, 3], ecvl.DataType.uint8, "xyc", ecvl.ColorType.RGB)
    a = np.array(x, copy=False)
    a.fill(128)
    x.ConvertTo(ecvl.DataType.int8, True)
    assert x.elemtype_ == ecvl.DataType.int8
    a = np.array(x, copy=False)
    assert (a == 127).all()
    # saturate = True by default
    x = ecvl.Image([2, 4, 3], ecvl.DataType.uint8, "xyc", ecvl.ColorType.RGB)
    a = np.array(x, copy=False)
    a.fill(128)
    x.ConvertTo(ecvl.DataType.int8)
    assert x.elemtype_ == ecvl.DataType.int8
    a = np.array(x, copy=False)
    assert (a == 127).all()
