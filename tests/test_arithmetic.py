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
    ecvl.Neg(z)
    assert (d == -10).all()


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_And(ecvl):
    dims = [2, 3, 1]
    x = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.GRAY)
    y = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.GRAY)
    a = np.array(x, copy=False)
    b = np.array(y, copy=False)
    tmp = _empty_img(ecvl)
    a.fill(5)
    b.fill(14)
    ecvl.And(x, y, tmp)
    c = np.array(tmp, copy=False)
    assert (c == (5 & 14)).all()


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_Or(ecvl):
    dims = [2, 3, 1]
    x = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.GRAY)
    y = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.GRAY)
    a = np.array(x, copy=False)
    b = np.array(y, copy=False)
    tmp = _empty_img(ecvl)
    a.fill(5)
    b.fill(14)
    ecvl.Or(x, y, tmp)
    c = np.array(tmp, copy=False)
    assert (c == (5 | 14)).all()
