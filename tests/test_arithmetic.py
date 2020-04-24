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
