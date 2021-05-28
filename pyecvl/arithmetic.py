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

from .datatype import DataType
from . import _core
_ecvl = _core.ecvl


__all__ = [
    "Neg",
    "Add",
    "Sub",
    "Mul",
    "Div",
]


def Neg(src, dst, dst_type=DataType.none, saturate=True):
    """\
    In-place negation of an image.

    Negates every value of ``src``, and stores the the result in ``dst``
    with the specified type.

    :param src: source image
    :param dst: destination image
    :param dst_type: destination image DataType
    :param saturate: whether to apply saturation
    :return: None
    """
    return _ecvl.Neg(src, dst, dst_type, saturate)


def Add(src1, src2, dst, dst_type=DataType.none, saturate=True):
    """\
    Add two images.

    Adds ``src1`` to ``src2`` and stores the the result in ``dst`` with the
    specified type.

    :param src1: source image 1
    :param src2: source image 2
    :param dst: destination image
    :param dst_type: destination image DataType
    :param saturate: whether to apply saturation
    :return: None

    """
    return _ecvl.Add(src1, src2, dst, dst_type, saturate)


def Sub(src1, src2, dst, dst_type=DataType.none, saturate=True):
    """\
    Subtract an image from another.

    Subtracts ``src2`` from ``src1`` and stores the the result in ``dst`` with
    the specified type.

    :param src1: source image 1
    :param src2: source image 2
    :param dst: destination image
    :param dst_type: destination image DataType
    :param saturate: whether to apply saturation
    :return: None
    """
    return _ecvl.Sub(src1, src2, dst, dst_type, saturate)


def Mul(src1, src2, dst, dst_type=DataType.none, saturate=True):
    """\
    Multiply two images.

    Muliplies ``src1`` by ``src2`` and stores the the result in ``dst`` with
    the specified type.

    :param src1: source image 1
    :param src2: source image 2
    :param dst: destination image
    :param dst_type: destination image DataType
    :param saturate: whether to apply saturation
    :return: None
    """
    return _ecvl.Mul(src1, src2, dst, dst_type, saturate)


def Div(src1, src2, dst, dst_type=DataType.none, saturate=True):
    """\
    Divide an image by another.

    Divides ``src1`` by ``src2`` and stores the the result in ``dst`` with
    the specified type.

    :param src1: source image 1
    :param src2: source image 2
    :param dst: destination image
    :param dst_type: destination image DataType
    :param saturate: whether to apply saturation
    :return: None
    """
    return _ecvl.Div(src1, src2, dst, dst_type, saturate)
