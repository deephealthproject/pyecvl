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

from datetime import timedelta

from .image import ColorType
from . import _core
_ecvl = _core.ecvl


if not _ecvl.ECVL_EDDL:
    raise ImportError("extension module not compiled with EDDL support")


__all__ = [
    "DatasetAugmentations",
    "DLDataset",
    "MakeGrid",
    "ImageToTensor",
    "ProducersConsumerQueue",
    "TensorToImage",
    "TensorToView",
    "ThreadCounters",
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


class DLDataset(_ecvl.DLDataset):
    r"""\
    DeepHealth deep learning dataset.

    :var n_channels\_: number of image channels
    :var n_channels_gt\_: number of ground truth image channels
    :var resize_dims\_: dimensions ``[H, W]`` to which images must be resized
    """
    def __init__(self, filename, batch_size, augs, ctype=ColorType.RGB,
                 ctype_gt=ColorType.GRAY, num_workers=1, queue_ratio_size=1,
                 drop_last=None, verify=False):
        """\
        :param filename: path to the dataset file
        :param batch_size: size of each dataset mini batch
        :param augs: a DatasetAugmentations object specifying the training,
          validation and test augmentations to be applied to the dataset images
          (and ground truth if existing) for each split. Set to None if no
          augmentation is required
        :param ctype: ColorType of the dataset images
        :param ctype_gt: ColorType of the dataset ground truth images
        :param num_workers: number of parallel threads spawned
        :param queue_ratio_size: the producers-consumer queue will have a
          maximum size equal to ``batch_size`` x ``queue_ratio_size``
          x ``num_workers``
        :param drop_last: For each split, whether to drop the last samples
          that don't fit the batch size. The vector dimensions must match the
          number of splits.
        :param verify: if True, verify image existence
        """
        if drop_last is None:
            drop_last = []
        _ecvl.DLDataset.__init__(
            self, filename, batch_size, augs, ctype, ctype_gt, num_workers,
            queue_ratio_size, drop_last, verify
        )

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

    def LoadBatch(self, images, labels=None):
        """\
        Load a batch into the images and labels tensors.

        :param images: a Tensor to store the batch of images
        :param labels: a Tensor to store the batch of labels
        """
        if labels is None:
            return _ecvl.DLDataset.LoadBatch(self, images)
        return _ecvl.DLDataset.LoadBatch(self, images, labels)

    @staticmethod
    def SetSplitSeed(seed):
        """\
        Set a fixed seed for the randomly generated values.

        Useful to reproduce experiments with same shuffling during training.

        :param seed: seed for the random engine
        """
        return _ecvl.DLDataset.SetSplitSeed(seed)

    def SetBatchSize(self, bs):
        """\
        Set the batch size.

        Note that this does not affect the EDDL network's batch size.

        :param bs: value of the batch size
        """
        return _ecvl.DLDataset.SetBatchSize(self, bs)

    def ProduceImageLabel(self, augs, elem):
        """\
        Load a sample and its label and push them to the producers-consumer queue.

        :param augs: DatasetAugmentations to apply to the sample image
        :param elem: Sample to load and push
        """
        return _ecvl.DLDataset.ProduceImageLabel(self, augs, elem)

    def ThreadFunc(self, thread_index):
        """\
        Called when a thread is spawned.

        ``ProduceImageLabel`` is called for each sample handled by the thread.

        :param thread_index: index of the thread
        """
        return _ecvl.DLDataset.ThreadFunc(self, thread_index)

    def GetBatch(self):
        """\
        Pop ``batch_size`` samples from the queue and copy them into tensors.

        :return: a tuple of three elements: a vector of samples; a tensor
          containing the image; a tensor containing the label.
        """
        return _ecvl.DLDataset.GetBatch(self)

    def Start(self, split_index=-1):
        """\
        Spawn ``num_workers`` threads.

        :param split_index: index of the split for ``GetBatch`` (default = current)
        """
        return _ecvl.DLDataset.Start(self, split_index)

    def Stop(self):
        """\
        Join all threads.
        """
        return _ecvl.DLDataset.Stop(self)

    def GetQueueSize(self):
        """\
        Get the current size of the producers-consumer queue.

        :return: size of the queue
        """
        return _ecvl.DLDataset.GetQueueSize(self)

    def SetAugmentations(self, da):
        """\
        Set the dataset augmentations.

        :param da: DatasetAugmentations to set
        """
        return _ecvl.DLDataset.SetAugmentations(self, da)

    def GetNumBatches(self, split=-1):
        """\
        Get the number of batches in the specified split.

        By default, return the number of batches in the current split.

        :param split: index, name or ``SplitType`` of the split from which
          to get the number of batches.
        """
        return _ecvl.DLDataset.GetNumBatches(self, split)

    def ToTensorPlane(self, label):
        """\
        Convert the sample labels into a one-hot encoded tensor.

        :param label: list of sample labels
        """
        return _ecvl.DLDataset.ToTensorPlane(self, label)

    def SetWorkers(self, num_workers):
        """\
        Set the number of workers.

        :param num_workers: number of worker threads to spawn
        """
        return _ecvl.DLDataset.SetWorkers(self, num_workers)

    def SetNumChannels(self, n_channels, n_channels_gt=1):
        """\
        Change the number of channels of the image produced by ECVL and update
        the internal EDDL tensors shape accordingly.

        Useful for custom data loading.

        :param n_channels: number of channels of input image
        :param n_channels_gt: number of channels of ground truth
        """
        return _ecvl.DLDataset.SetNumChannels(self, n_channels, n_channels_gt)

    def sleep_for(self, delta):
        """\
        Block the execution of the current thread for the specified duration.

        :param delta: a datetime.timedelta representing the sleep duration. If
          a different type is provided, conversion to a timedelta with
          seconds = delta will be attempted.
        """
        if not isinstance(delta, timedelta):
            delta = timedelta(seconds=delta)
        _ecvl.DLDataset.sleep_for(self, delta)


class ProducersConsumerQueue(_ecvl.ProducersConsumerQueue):
    """\
    Manages the producers-consumer queue of samples.
    """
    def __init__(self, mxsz=None, thresh=None):
        if mxsz is None:
            _ecvl.ProducersConsumerQueue.__init__(self)
        elif thresh is None:
            _ecvl.ProducersConsumerQueue.__init__(self, mxsz)
        else:
            _ecvl.ProducersConsumerQueue.__init__(self, mxsz, thresh)

    def Push(self, sample, image, label):
        """\
        Push a sample.

        Lock the queue's mutex, wait until the queue is not full and push a
        sample, image, label tuple into the queue.

        :param sample: sample to push
        :param image: image (as a Tensor) to push
        :param label: label (as a Tensor) to push
        """
        return _ecvl.ProducersConsumerQueue.Push(self, sample, image, label)

    def Pop(self):
        """\
        Pop a sample.

        Lock the queue's mutex, wait until the queue is not empty and pop a
        sample, image, label tuple from the queue.

        :return: sample (as a Tensor), image (as a Tensor), label tuple
        """
        return _ecvl.ProducersConsumerQueue.Pop(self)

    def IsFull(self):
        """\
        Check whether the queue is full or not.

        :return: True if the queue is full, False otherwise
        """
        return _ecvl.ProducersConsumerQueue.IsFull(self)

    def IsEmpty(self):
        """\
        Check whether the queue is empty or not.

        :return: True if the queue is empty, False otherwise
        """
        return _ecvl.ProducersConsumerQueue.IsEmpty(self)

    def Length(self):
        """\
        Return the current size of the queue.

        :return: queue size
        """
        return _ecvl.ProducersConsumerQueue.Length(self)

    def SetSize(self, max_size, thresh=-1):
        """\
        Set the maximum size of the queue.

        :param max_size: maximum queue size
        :param thresh: threshold from which to restart producing samples. If
          not specified, it's set to half the maximum size.
        """
        return _ecvl.ProducersConsumerQueue.SetSize(self, max_size, thresh)

    def Clear(self):
        """\
        Remove all elements from the queue.
        """
        return _ecvl.ProducersConsumerQueue.Clear(self)


class ThreadCounters(_ecvl.ThreadCounters):
    """\
    Manages the thread counters.

    Each thread manages its own indices.

    :var counter_: index of the sample currently used by the thread
    :var min_: smallest sample index managed by the thread
    :var max_: largest sample index managed by the thread
    """
    def __init__(self, *args):
        """\
        Can be called with two or three arguments. In the former case, it sets
        ``min_`` and ``max_``; in the latter, it sets ``counter_``, ``min_``
        and ``max_``.
        """
        if len(args) < 2 or len(args) > 3:
            raise ValueError("wrong number of arguments")
        _ecvl.ThreadCounters.__init__(self, *args)

    def Reset(self):
        """\
        Reset the thread counter to its minimum value.
        """
        return _ecvl.ThreadCounters.Reset(self)


def ImageToTensor(img, t=None, offset=None):
    """\
    Convert an ECVL Image to an EDDL Tensor.

    The input image must have 3 dimensions "xy[czo]" (in any order). The output
    tensor's dimensions will be C x H x W, where:

    * C = channels
    * H = height
    * W = width

    If ``t`` and ``offset`` are not specified, a new tensor is created with
    the above shape. Otherwise, the specified image is inserted into the
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
    if t is None or offset is None:
        raise ValueError("Either both or none of t and offset must be specified")
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


def MakeGrid(t, cols=8, normalize=False):
    """\
    Generate a grid of images from an EDDL tensor.

    :param t: B x C x H x W Tensor
    :param cols: number of images per row
    :param normalize: If ``True``, convert the image to the ``[0, 1]`` range
    :return: image grid as an Image
    """
    return _ecvl.MakeGrid(t, cols, normalize)
