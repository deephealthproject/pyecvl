# Copyright (c) 2019-2022 CRS4
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

import pytest

import pyecvl._core.ecvl as ecvl_core
import pyecvl.ecvl as ecvl_py


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_MetaData(ecvl):
    for n in -12, 12, -66000, 66000, -4294967300, 4294967300:
        m = ecvl.MetaData(n)
        assert m.Get() == n
        assert int(m.GetStr()) == n
    for n in -12.0, 12.0, -5e40, 5e40:
        m = ecvl.MetaData(n)
        assert m.Get() == pytest.approx(n)
        assert float(m.GetStr()) == pytest.approx(n)
    m = ecvl.MetaData("foo")
    assert m.Get() == "foo"
    assert m.GetStr() == "foo"
