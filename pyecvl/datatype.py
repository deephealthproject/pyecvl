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

from . import _core
_ecvl = _core.ecvl


__all__ = [
    "DataType",
    "DataTypeSize",
    "DataTypeSignedSize",
]


class DataType(_ecvl.DataType):
    """\
    Enum class which defines data types allowed for images.
    """
    int8 = _ecvl.DataType.int8
    int16 = _ecvl.DataType.int16
    int32 = _ecvl.DataType.int32
    int64 = _ecvl.DataType.int64
    float32 = _ecvl.DataType.float32
    float64 = _ecvl.DataType.float64
    uint8 = _ecvl.DataType.uint8
    uint16 = _ecvl.DataType.uint16
    none = _ecvl.DataType.none


def DataTypeSize(dt=None):
    """\
    Get the size in bytes of a given DataType.

    With no arguments, get the number of existing DataType members.

    :param dt: a DataType.
    :return: the DataType size in bytes, or the number of existing DataType
      members if called with no arguments
    """
    if dt is None:
        return _ecvl.DataTypeSize()
    return _ecvl.DataTypeSize(dt)


def DataTypeSignedSize():
    """\
    Get the number of existing signed DataType members.

    :return: the number of existing signed DataType members
    """
    return _ecvl.DataTypeSignedSize()
