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

from . import _core
_ecvl = _core.ecvl


# == datatype ==

class DataType(_ecvl.DataType):
    pass


def DataTypeSize(dt=None):
    if dt is None:
        return _ecvl.DataTypeSize()
    return _ecvl.DataTypeSize(dt)


def DataTypeSignedSize():
    return _ecvl.DataTypeSignedSize()


# == image ==

class ColorType(_ecvl.ColorType):
    pass


class Image(_ecvl.Image):
    pass


class View_int8(_ecvl.View_int8):
    pass


class View_int16(_ecvl.View_int16):
    pass


class View_float32(_ecvl.View_float32):
    pass


def CopyImage(src, dst, new_type=None):
    if new_type is None:
        return _ecvl.CopyImage(src, dst)
    return _ecvl.CopyImage(src, dst, new_type)


def RearrangeChannels(src, dst, channels, new_type=None):
    if new_type is None:
        return _ecvl.RearrangeChannels(src, dst, channels)
    return _ecvl.RearrangeChannels(src, dst, channels, new_type)


# == arithmetic ==

def And(src1, src2, dst):
    return _ecvl.And(src1, src2, dst)


def Neg(img):
    return _ecvl.Neg(img)


def Or(src1, src2, dst):
    return _ecvl.Or(src1, src2, dst)
