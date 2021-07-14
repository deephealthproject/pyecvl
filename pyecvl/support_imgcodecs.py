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
    "ImReadMode",
    "ImRead",
    "ImWrite",
]


class ImReadMode(_ecvl.ImReadMode):
    """\
    Enum class representing the possible image read modes.
    """
    UNCHANGED = _ecvl.ImReadMode.UNCHANGED
    GRAYSCALE = _ecvl.ImReadMode.GRAYSCALE
    COLOR = _ecvl.ImReadMode.COLOR
    ANYCOLOR = _ecvl.ImReadMode.ANYCOLOR


def ImRead(filename, flags=None):
    """\
    Load an image from a file.

    :param filename: name of the input file
    :param flags: an ImReadMode indicating how to read the image
    :return: an Image object
    """
    if flags is None:
        return _ecvl.ImRead(filename)
    return _ecvl.ImRead(filename, flags)


def ImWrite(filename, src):
    """\
    Save an image to a file.

    The image format is chosen based on the filename extension.

    :param filename: name of the output file
    :param src: Image to be saved
    :return: None
    """
    return _ecvl.ImWrite(filename, src)
