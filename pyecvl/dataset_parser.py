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

from .image import ColorType
from . import _core
_ecvl = _core.ecvl


__all__ = [
    "SplitType",
    "Sample",
    "Split",
    "Dataset",
]


class SplitType(_ecvl.SplitType):
    """\
    Enum class representing the supported split types.
    """
    training = _ecvl.SplitType.training
    validation = _ecvl.SplitType.validation
    test = _ecvl.SplitType.test


class Sample(_ecvl.Sample):
    r"""\
    Sample image in a dataset.

    Provides the information to describe a dataset sample.

    :var location\_: absolute path(s) of the sample (list of strings)
    :var label_path\_: absolute path of the sample's ground truth
    :var label\_: sample labels (list of integers)
    :var values\_: feature index-to-value mapping
    :var size\_: original x and y dimensions of the sample
    """
    def LoadImage(self, ctype=ColorType.BGR, is_gt=False):
        """\
        Return the dataset image for this sample.

        Opens the sample image from ``location_`` or ``label_path_``, depending
        on the ``is_gt`` parameter.

        :param ctype: ColorType of the returned image
        :param is_gt: whether to load the sample image or its ground truth
        :return: sample image
        """
        return _ecvl.Sample.LoadImage(self, ctype, is_gt)


class Split(_ecvl.Split):
    r"""\
    Provides the splits a dataset can have: training, validation, and test.

    :var training\_: training samples indices (list of integers)
    :var validation\_: validation samples indices (list of integers)
    :var test\_: test samples indices (list of integers)
    """


class Dataset(_ecvl.Dataset):
    r"""\
    DeepHealth Dataset.

    Implements the `DeepHealth Dataset Format
    <https://github.com/deephealthproject/ecvl/wiki/DeepHealth-Toolkit-Dataset-Format>`_.

    :var name\_: dataset name
    :var description\_: dataset description
    :var classes\_: classes available in the dataset (list of strings)
    :var features\_: features available in the dataset (list of strings)
    :var samples\_: list of dataset samples
    :var split\_: dataset splits
    """
    def __init__(self, filename):
        """\
        :param filename: path to the dataset file
        """
        _ecvl.Dataset.__init__(self, filename)

    def Dump(self, path):
        """\
        Dump the dataset to YAML following the DeepHealth Dataset Format.

        The YAML file is saved into the dataset's root directory. Sample paths
        are relative to the dataset's root directory.

        :param path: output file path
        :return: None
        """
        _ecvl.Dataset.Dump(self, path)
