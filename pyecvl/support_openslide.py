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

from . import _core
_ecvl = _core.ecvl


if not _ecvl.ECVL_WITH_OPENSLIDE:
    raise ImportError("extension module not compiled with OpenSlide support")


__all__ = [
    "OpenSlideImage",
]


class OpenSlideImage(_ecvl.OpenSlideImage):
    """\
    Openslide image.
    """
    def __init__(self, filename):
        """\
        :param filename: path to the image file
        """
        _ecvl.OpenSlideImage.__init__(self, filename)
        self.closed = False

    def GetLevelCount(self):
        """\
        Get the number of levels in the image.

        :return: number of levels in the image
        """
        return _ecvl.OpenSlideImage.GetLevelCount(self)

    def GetLevelsDimensions(self):
        """\
        Get the width and height for each level of a whole-slide image.

        :return: a list of pairs representing the width and height of each level
        """
        return _ecvl.OpenSlideImage.GetLevelsDimensions(self)

    def GetLevelDownsamples(self):
        """\
        Get the downsampling factor (or -1, if an error occurred) for each
        level.

        :return: list of floats representing the downsampling factor for each
          level
        """
        return _ecvl.OpenSlideImage.GetLevelDownsamples(self)

    def GetBestLevelForDownsample(self, downsample):
        """\
        Get the best level to use for displaying the given downsample.

        :param downsample: the desired downsample factor
        :return: image level, or -1 if an error occurred.
        """
        return _ecvl.OpenSlideImage.GetBestLevelForDownsample(self, downsample)

    def GetProperties(self, dst):
        """\
        Load metadata properties into an ECVL Image.

        :param dst: ECVL Image
        :return: None
        """
        return _ecvl.OpenSlideImage.GetProperties(self, dst)

    def ReadRegion(self, level, dims):
        """\
        Load a region of a whole-slide image.

        Supported formats are those supported by the OpenSlide library. If
        the region cannot be read for any reason, the function creates an
        empty Image and returns False.

        :param level: image level to read
        :param dims: ``[x, y, w, h]`` list, where: ``x`` and ``y`` are the top
          left x and y coordinates in the level 0 reference frame; ``w`` and
          ``h`` are the width and height of the region.
        :return: ECVL Image (RGB, with a "cxy" layout).
        """
        return _ecvl.OpenSlideImage.ReadRegion(self, level, dims)

    def Close(self):
        """\
        Close the file handle.

        :return: None
        """
        if not self.closed:
            self.closed = True
            return _ecvl.OpenSlideImage.Close(self)

    def __enter__(self):
        return self

    def __exit__(self, *args):
        self.Close()
