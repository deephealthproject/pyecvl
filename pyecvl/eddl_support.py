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


if not _ecvl.ECVL_EDDL:
    raise ImportError("extension module not compiled with EDDL support")


__all__ = [
    "DatasetAugmentations",
    "DLDataset",
    "ImageToTensor",
    "TensorToImage",
    "TensorToView",
]


class DatasetAugmentations(_ecvl.DatasetAugmentations):
    """\
    Represents the augmentations which will be applied to each split.
    """
    def __init__(self, augs):
        """\
        :param augs: augmentations to be applied to each split.
        """
        _ecvl.DatasetAugmentations.__init__(self, augs)

    def Apply(self, st, img, gt=None):
        """\
        Apply augmentations for the specified split to an image.

        :param st: a SplitType specifying which set of augmentations
          should be applied
        :param img: image to which augmentations should be applied
        :param gt: ground truth image to which augmentations should be applied
        :return: None
        """
        if gt is None:
            return _ecvl.DatasetAugmentations.Apply(self, st, img)
        return _ecvl.DatasetAugmentations.Apply(self, st, img, gt)


class LabelClass(_ecvl.LabelClass):
    """\
    Label for classification tasks.
    """
    def ToTensorPlane(self, tensor, offset):
        """\
        Convert the sample labels to a one-hot encoded tensor and copy it to
        the batch tensor.

        :param tensor: copy labels to this EDDL Tensor (dimensions:
          batch_size x num_classes)
        :param offset: position of the tensor from which to insert the labels
        """
        return _ecvl.LabelClass.ToTensorPlane(self, tensor, offset)


class LabelImage(_ecvl.LabelImage):
    """\
    Label for segmentation tasks.
    """
    def ToTensorPlane(self, tensor, offset):
        """\
        Convert the sample ground truth image to a tensor and copy it to
        the batch tensor.

        :param tensor: copy ground truth to this EDDL Tensor (dimensions:
          batch_size x num_classes x height x width)
        :param offset: position of the tensor from which to insert the gt
        """
        return _ecvl.LabelImage.ToTensorPlane(self, tensor, offset)


class DLDataset(_ecvl.DLDataset):
    r"""\
    DeepHealth deep learning dataset.

    :var batch_size\_: size of each dataset mini batch
    :var n_channels\_: number of image channels
    :var n_channels_gt\_: number of ground truth image channels
    :var current_split\_: = Current SplitType from which images are loaded
    :var resize_dims\_: dimensions ``[H, W]`` to which images must be resized
    :var current_batch\_: number of batches already loaded for each split
    :var ctype\_: ColorType of the dataset images
    :var ctype_gt\_: ColorType of the dataset ground truth images
    :var augs\_: DatasetAugmentations to be applied to the dataset images
      (and ground truth if existing) for each split
    """
    def __init__(self, filename, batch_size, augs=None, ctype=ColorType.BGR,
                 ctype_gt=ColorType.GRAY, verify=False):
        """\
        :param filename: path to the dataset file
        :param batch_size: size of each dataset mini batch
        :param augs: a DatasetAugmentations object specifying the training,
          validation and test augmentations to be applied to the dataset images
          (and ground truth if existing) for each split. Set to None if no
          augmentation is required
        :param ctype: ColorType of the dataset images
        :param ctype_gt: ColorType of the dataset ground truth images
        :param verify: if True, verify image existence
        """
        if augs is None:
            augs = _ecvl.DatasetAugmentations()
        _ecvl.DLDataset.__init__(
            self, filename, batch_size, augs, ctype, ctype_gt
        )

    def GetSplit(self, split=None):
        """\
        Get the image indexes for a split.

        :param split: a SplitType; if None, will default to the current split
        :return: list of image indexes for the split
        """
        if split is None:
            return _ecvl.DLDataset.GetSplit(self)
        return _ecvl.DLDataset.GetSplit(self, split)

    def ResetBatch(self, split=-1, shuffle=False):
        """\
        Reset the batch counter and optionally shuffle the split's sample
        indices.

        If a negative value is provided, the current split is reset (default).

        :param split: index, name or SplitType of the split
        :param shuffle: whether to shuffle the split's sample indices
        :return: None
        """
        return _ecvl.DLDataset.ResetBatch(self, split, shuffle)

    def ResetAllBatches(self, shuffle=False):
        """\
        Reset the batch counter of each split.

        :param shuffle: whether to shuffle each split's sample indices
        :return: None
        """
        return _ecvl.DLDataset.ResetAllBatches(self, shuffle)

    def SetSplit(self, split):
        """\
        Set the current Split.

        :param split: a SplitType
        :return: None
        """
        return _ecvl.DLDataset.SetSplit(self, split)

    def LoadBatch(self, images, labels=None):
        """\
        Load a batch into the images and labels tensors.

        :param images: a Tensor to store the batch of images
        :param labels: a Tensor to store the batch of labels
        """
        if labels is None:
            return _ecvl.DLDataset.LoadBatch(self, images)
        return _ecvl.DLDataset.LoadBatch(self, images, labels)


def ImageToTensor(img, t=None, offset=None):
    """\
    Convert an ECVL Image to an EDDL Tensor.

    The input image must have 3 dimensions "xy[czo]" (in any order). The output
    tensor's dimensions will be C x H x W, where:

    * C = channels
    * H = height
    * W = width

    If ``t`` and ``offset`` are None, a new tensor is created with the above
    shape. Otherwise, they are inserted into the
    existing ``t`` tensor at the specified offset. This allows to insert more
    than one image into a tensor, specifying how many images are already
    stored in it.

    :param img: input image
    :param t: output tensor
    :param offset: how many images are already stored in the tensor
    :return: output tensor
    """
    if t is None and offset is None:
        return _ecvl.ImageToTensor(img)
    else:
        _ecvl.ImageToTensor(img, t, offset)
        return t


def TensorToImage(t):
    """\
    Convert an EDDL Tensor into an ECVL Image.

    Tensor dimensions must be C x H x W or N x C x H x W, where:

    * N = batch size
    * C = channels
    * H = height
    * W = width

    The output image will be "xyo" with DataType.float32 and ColorType.none.

    :param t: input tensor.
    :return: output image
    """
    return _ecvl.TensorToImage(t)


def TensorToView(t):
    return _ecvl.TensorToView(t)
