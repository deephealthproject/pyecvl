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


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_Neg(ecvl):
    dims = [2, 3, 1]
    z = ecvl.Image(dims, ecvl.DataType.int8, "xyc", ecvl.ColorType.GRAY)
    d = np.array(z, copy=False)
    d.fill(10)
    tmp = _empty_img(ecvl)
    # basic call
    ecvl.Neg(z, tmp)
    tmp_arr = np.array(tmp, copy=False)
    assert (tmp_arr == -10).all()
    # data type
    d.fill(20)
    ecvl.Neg(z, tmp, ecvl.DataType.int16)
    tmp_arr = np.array(tmp, copy=False)
    assert (tmp_arr == -20).all()
    assert (tmp_arr.dtype == np.int16)
    # saturate
    d.fill(-128)
    ecvl.Neg(z, tmp, ecvl.DataType.int8, True)
    tmp_arr = np.array(tmp, copy=False)
    assert (tmp_arr == 127).all()
    ecvl.Neg(z, tmp, ecvl.DataType.int8, False)
    tmp_arr = np.array(tmp, copy=False)
    assert (tmp_arr == -128).all()


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_Add(ecvl):
    x = ecvl.Image([2, 4, 3], ecvl.DataType.int8, "xyc", ecvl.ColorType.RGB)
    y = ecvl.Image([2, 4, 3], ecvl.DataType.int8, "xyc", ecvl.ColorType.RGB)
    a = np.array(x, copy=False)
    b = np.array(y, copy=False)
    a.fill(10)
    b.fill(3)
    z = _empty_img(ecvl)
    # basic call
    ecvl.Add(x, y, z)
    c = np.array(z, copy=False)
    assert (c == 13).all()
    # data type
    a.fill(20)
    ecvl.Add(x, y, z, ecvl.DataType.int16)
    c = np.array(z, copy=False)
    assert (c == 23).all()
    assert (c.dtype == np.int16)
    # saturate
    a.fill(10)
    b.fill(118)
    ecvl.Add(x, y, z, ecvl.DataType.int8, True)
    c = np.array(z, copy=False)
    assert (c == 127).all()
    ecvl.Add(x, y, z, ecvl.DataType.int8, False)
    c = np.array(z, copy=False)
    assert (c == -128).all()


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_sub(ecvl):
    x = ecvl.Image([2, 4, 3], ecvl.DataType.int8, "xyc", ecvl.ColorType.RGB)
    y = ecvl.Image([2, 4, 3], ecvl.DataType.int8, "xyc", ecvl.ColorType.RGB)
    a = np.array(x, copy=False)
    b = np.array(y, copy=False)
    a.fill(-10)
    b.fill(3)
    z = _empty_img(ecvl)
    # basic call
    ecvl.Sub(x, y, z)
    c = np.array(z, copy=False)
    assert (c == -13).all()
    # data type
    a.fill(-20)
    ecvl.Sub(x, y, z, ecvl.DataType.int16)
    c = np.array(z, copy=False)
    assert (c == -23).all()
    assert (c.dtype == np.int16)
    # saturate
    a.fill(-10)
    b.fill(119)
    ecvl.Sub(x, y, z, ecvl.DataType.int8, True)
    c = np.array(z, copy=False)
    assert (c == -128).all()
    ecvl.Sub(x, y, z, ecvl.DataType.int8, False)
    c = np.array(z, copy=False)
    assert (c == 127).all()


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_mul(ecvl):
    x = ecvl.Image([2, 4, 3], ecvl.DataType.int8, "xyc", ecvl.ColorType.RGB)
    y = ecvl.Image([2, 4, 3], ecvl.DataType.int8, "xyc", ecvl.ColorType.RGB)
    a = np.array(x, copy=False)
    b = np.array(y, copy=False)
    a.fill(16)
    b.fill(3)
    z = _empty_img(ecvl)
    # basic call
    ecvl.Mul(x, y, z)
    c = np.array(z, copy=False)
    assert (c == 48).all()
    # data type
    a.fill(20)
    ecvl.Mul(x, y, z, ecvl.DataType.int16)
    c = np.array(z, copy=False)
    assert (c == 60).all()
    assert (c.dtype == np.int16)
    # saturate
    a.fill(16)
    b.fill(8)
    ecvl.Mul(x, y, z, ecvl.DataType.int8, True)
    c = np.array(z, copy=False)
    assert (c == 127).all()
    ecvl.Mul(x, y, z, ecvl.DataType.int8, False)
    c = np.array(z, copy=False)
    assert (c == -128).all()


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_div(ecvl):
    x = ecvl.Image([2, 4, 3], ecvl.DataType.int16, "xyc", ecvl.ColorType.RGB)
    y = ecvl.Image([2, 4, 3], ecvl.DataType.int16, "xyc", ecvl.ColorType.RGB)
    a = np.array(x, copy=False)
    b = np.array(y, copy=False)
    a.fill(11)
    b.fill(2)
    z = _empty_img(ecvl)
    # basic call
    ecvl.Div(x, y, z)
    c = np.array(z, copy=False)
    assert (c == 5).all()
    # data type
    a.fill(20)
    ecvl.Div(x, y, z, ecvl.DataType.int8)
    c = np.array(z, copy=False)
    assert (c == 10).all()
    assert (c.dtype == np.int8)
    # saturate
    a.fill(1280)
    b.fill(10)
    ecvl.Div(x, y, z, ecvl.DataType.int8, True)
    c = np.array(z, copy=False)
    # assert (c == 127).all()  # bug in ecvl::Div?
    ecvl.Div(x, y, z, ecvl.DataType.int8, False)
    c = np.array(z, copy=False)
    # assert (c == -128).all()  # bug in ecvl::Div?
