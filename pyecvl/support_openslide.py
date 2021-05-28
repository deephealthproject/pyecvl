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


if not _ecvl.ECVL_WITH_OPENSLIDE:
    raise ImportError("extension module not compiled with OpenSlide support")


__all__ = [
    "OpenSlideGetLevels",
    "OpenSlideRead",
]


def OpenSlideGetLevels(filename):
    """\
    Get the width and height for each level of a whole-slide image.

    :param filename: image file name
    :return: a list of pairs representing the width and height of each level
    """
    return _ecvl.OpenSlideGetLevels(filename)


def OpenSlideRead(filename, level, dims):
    """\
    Load a region of a whole-slide image.

    Supported formats are those supported by the OpenSlide library.

    :param filename: image file name
    :param level: image level to extract
    :param dims: ``[x, y, w, h]`` list representing the region to extract.
      ``x`` and ``y`` are the top-left x and y coordinates in the level 0
      reference frame. ``w`` and ``h`` are the width and height of the region
    :return: an Image object
    """
    return _ecvl.OpenSlideRead(filename, level, dims)
