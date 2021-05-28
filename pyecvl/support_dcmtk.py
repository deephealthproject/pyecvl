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


if not _ecvl.ECVL_WITH_DICOM:
    raise ImportError("extension module not compiled with DCMTK support")


__all__ = [
    "DicomRead",
    "DicomWrite",
]


def DicomRead(filename):
    """\
    Loads a dicom image from a file.

    :param filename: image file name
    :return: an Image object
    """
    return _ecvl.DicomRead(filename)


def DicomWrite(filename, src):
    """\
    Save an image to a file in the DICOM format.

    :param filename: image file name
    :param src: image to be saved
    :return: None
    """
    return _ecvl.DicomWrite(filename, src)
