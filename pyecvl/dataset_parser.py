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
    "Task",
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


class Task(_ecvl.Task):
    """\
    Enum class representing allowed tasks for a dataset.
    """
    classification = _ecvl.Task.classification
    segmentation = _ecvl.Task.segmentation


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
    def LoadImage(self, ctype=ColorType.RGB, is_gt=False):
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
    Represents a subset of a dataset.

    :var split_name\_: split name (string)
    :var split_type\_: split type (SplitType), if the split name is
      "training", "validation" or "test"
    :var samples_indices\_: sample indices of the split (list of integers)
    :var drop_last\_: whether to drop elements that don't fit in the batch
      (boolean)
    :var num_batches\_: number of batches in this split (integer)
    :var last_batch\_: dimension of the last batch (integer)
    :var no_label\_: whether the split has samples with labels (boolean)
    """

    def __init__(self, split_name="", samples_indices=None, drop_last=False, no_label=False):
        """\
        :param split_name: name of the split
        :param samples_indices: indices of samples within the split
        :param drop_last: whether to drop elements that don't fit in the batch
        :param no_label: whether the split has samples with labels
        """
        if samples_indices is None:
            samples_indices = []
        _ecvl.Split.__init__(self, split_name, samples_indices, drop_last, no_label)

    def SetNumBatches(self, batch_size):
        """\
        Set the number of batches for the given batch size.

        :param batch_size: number of samples for each batch (except the last
          one, if drop_last is False and there is a remainder)
        """
        return _ecvl.Split.SetNumBatches(self, batch_size)

    def SetLastBatch(self, batch_size):
        """\
        Set the size of the last batch for the given batch size.


        :param batch_size: number of samples for each batch (except the last
          one, if drop_last is False and there is a remainder)
        """
        return _ecvl.Split.SetLastBatch(self, batch_size)


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
    :var current_split\_: current split from which images are loaded
    :var task\_: dataset task (classification or segmentation)
    """
    def __init__(self, filename):
        """\
        :param filename: path to the dataset file
        """
        _ecvl.Dataset.__init__(self, filename)

    def GetSplit(self, split=-1):
        """\
        Get the image indices of the specified split.

        By default, return the image indices of the current split.

        :param split: index, name or ``SplitType`` of the split to get
        :return: list of integers representing the image indices
        """
        return _ecvl.Dataset.GetSplit(self, split)

    def SetSplit(self, split):
        """\
        Set the current split.

        :param split: index, name or ``SplitType`` of the split to set
        """
        return _ecvl.Dataset.SetSplit(self, split)

    def Dump(self, path):
        """\
        Dump the dataset to YAML following the DeepHealth Dataset Format.

        The YAML file is saved into the dataset's root directory. Sample paths
        are relative to the dataset's root directory.

        :param path: output file path
        :return: None
        """
        return _ecvl.Dataset.Dump(self, path)

    def GetLocations(self):
        """\
        Get the locations of all samples in the dataset.

        Note that a single sample can have multiple locations (e.g., different
        acquisitions of the same image).

        :return: a list of lists of image paths
        """
        return _ecvl.Dataset.GetLocations(self)
