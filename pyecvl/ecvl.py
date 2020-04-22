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
    """\
    Enum class which defines data types allowed for images.
    """
    int8 = _ecvl.DataType.int8
    int16 = _ecvl.DataType.int16
    int32 = _ecvl.DataType.int32
    int64 = _ecvl.DataType.int64
    float32 = _ecvl.DataType.float32
    float64 = _ecvl.DataType.float64
    uint8 = _ecvl.DataType.uint8
    uint16 = _ecvl.DataType.uint16
    none = _ecvl.DataType.none


def DataTypeSize(dt=None):
    """\
    Get the size in bytes of a given DataType.

    With no arguments, get the number of existing DataType members.

    :param dt: a DataType.
    :return: the DataType size in bytes, or the number of existing DataType
      members if called with no arguments
    """
    if dt is None:
        return _ecvl.DataTypeSize()
    return _ecvl.DataTypeSize(dt)


def DataTypeSignedSize():
    """\
    Get the number of existing signed DataType members.

    :return: the number of existing signed DataType members
    """
    return _ecvl.DataTypeSignedSize()


# == image ==

class ColorType(_ecvl.ColorType):
    """\
    Enum class representing the supported color spaces.
    """
    none = _ecvl.ColorType.none
    GRAY = _ecvl.ColorType.GRAY
    RGB = _ecvl.ColorType.RGB
    RGBA = _ecvl.ColorType.RGBA
    BGR = _ecvl.ColorType.BGR
    HSV = _ecvl.ColorType.HSV
    YCbCr = _ecvl.ColorType.YCbCr


class Image(_ecvl.Image):
    """\
    Image class.
    """

    @staticmethod
    def empty():
        """\
        Create an empty image.

        :return: an empty image
        """
        return _ecvl.Image()

    @staticmethod
    def fromarray(array, channels, colortype, spacings=None):
        """\
        Create an image from a NumPy array.

        :param array: a NumPy array
        :param channels: channels string
        :param colortype: a ColorType
        :param spacings: spacings between pixels
        :return: an image containing the same data as the input array
        """
        if spacings is None:
            spacings = []
        return _ecvl.Image(array, channels, colortype, spacings)

    def __init__(self, dims, elemtype, channels, colortype, spacings=None):
        """\
        :param dims: image dimensions
        :param elemtype: pixel type, a DataType
        :param channels: channels string
        :param colortype: a ColorType
        :param spacings: spacings between pixels
        """
        if spacings is None:
            spacings = []
        _ecvl.Image.__init__(
            self, dims, elemtype, channels, colortype, spacings
        )

    def IsEmpty(self):
        """\
        Whether the image contains data or not.

        :return: True if the image contains data, False otherwise
        """
        return _ecvl.Image.IsEmpty(self)

    def IsOwner(self):
        """\
        Whether the image owns the data or not.

        :return: True if the image owns the data, False otherwise
        """
        return _ecvl.Image.IsOwner(self)

    def Channels(self):
        """\
        Get the number of channels.

        :return: number of channels
        """
        return _ecvl.Image.Channels(self)

    def Add(self, other, saturate=True):
        """\
        Add data from another image to this image's data.

        :param other: other image
        :param saturate: in case of overflow, set values to limit for data type
        :return: None
        """
        return _ecvl.Image.Add(self, other, saturate)

    def Sub(self, other, saturate=True):
        """\
        Subtract data from another image from this image's data.

        :param other: other image
        :param saturate: in case of overflow, set values to limit for data type
        :return: None
        """
        return _ecvl.Image.Sub(self, other, saturate)

    def Mul(self, other, saturate=True):
        """\
        Multiply data from this image by another image's data.

        :param other: other image
        :param saturate: in case of overflow, set values to limit for data type
        :return: None
        """
        return _ecvl.Image.Mul(self, other, saturate)

    def Div(self, other, saturate=True):
        """\
        Divide data from this image by another image's data.

        :param other: other image
        :param saturate: in case of overflow, set values to limit for data type
        :return: None
        """
        return _ecvl.Image.Div(self, other, saturate)


class View_int8(_ecvl.View_int8):
    pass


class View_int16(_ecvl.View_int16):
    pass


class View_float32(_ecvl.View_float32):
    pass


def CopyImage(src, dst, new_type=None):
    """\
    Copy data from the source image ``src`` to the destination image ``dst``.

    ``src`` and ``dst`` cannot be the same image. ``src`` cannot be an image
    with DataType.none. The optional ``new_type`` parameter can be used to
    change the DataType of the ``dst`` image.

    When the DataType is not specified:

    * if ``dst`` is empty, ``src`` will be directly copied into ``dst``

    * if ``src`` and ``dst`` have different size in memory or different
      channels and ``dst`` is the data owner, the procedure will overwrite
      ``dst`` creating a new image (channels and dimensions will be the same
      as ``src``, DataType will be the same as ``dst`` if they are not none or
      the same as ``src`` otherwise)

    * if ``src`` and ``dst`` have different size in memory or different
      channels and ``dst`` is not the data owner, the procedure will throw an
      exception

    * if ``src`` and ``dst`` have different color types and ``dst`` is the
      data owner, the procedure produces a ``dst`` image with the same color
      type as ``src``

    * if ``src`` and ``dst`` have different color types and ``dst`` is not the
      data owner, the procedure will throw an exception

    When the DataType is specified the function has the same behavior, but
    ``dst`` will have the specified DataType.

    :param src: source image
    :param dst: destination image
    :param new_type: new DataType for the destination image
    :return: None
    """
    if new_type is None:
        return _ecvl.CopyImage(src, dst)
    return _ecvl.CopyImage(src, dst, new_type)


def RearrangeChannels(src, dst, channels, new_type=None):
    """\
    Change image dimensions order.

    Changes the order of the ``src`` image dimensions, saving the result into
    the ``dst`` image. The new order can be specified as a string through the
    ``channels`` parameter. ``src`` and ``dst`` can be the same image.

    :param src: source image
    :param dst: destination image
    :param channels: new order for the image channels, as a string
    :param new_type: new DaatType for the destination image. If None, the
      destination image will preserve its type if it is not empty, otherwise
      it will have the same type as the source Image
    """
    if new_type is None:
        return _ecvl.RearrangeChannels(src, dst, channels)
    return _ecvl.RearrangeChannels(src, dst, channels, new_type)


# == arithmetic ==

def And(src1, src2, dst):
    """\
    Boolean ``and`` between two images.

    Performs boolean ``and`` between two images with DataType.uint8 and
    ColorType.GRAY. The result is stored into ``dst``.

    :param src1: first image operand
    :param src2: second image operand
    :param dst: destination image
    :return: None
    """
    return _ecvl.And(src1, src2, dst)


def Neg(img):
    """\
    In-place negation of an image.

    Negates every value of ``img``, and stores the the result in the same
    image. The type of the image is not changed.

    :param img: image to be negated
    :return: negated image
    """
    return _ecvl.Neg(img)


def Or(src1, src2, dst):
    """\
    Boolean ``or`` between two images.

    Performs boolean ``or`` between two images with DataType.uint8 and
    ColorType.GRAY. The result is stored into ``dst``.

    :param src1: first image operand
    :param src2: second image operand
    :param dst: destination image
    :return: None
    """
    return _ecvl.Or(src1, src2, dst)


# == imgproc ==

class ThresholdingType(_ecvl.ThresholdingType):
    pass


class InterpolationType(_ecvl.InterpolationType):
    pass


class MorphTypes(_ecvl.MorphTypes):
    pass


class InpaintTypes(_ecvl.InpaintTypes):
    pass


def ResizeDim(src, dst, newdims, interp=InterpolationType.linear):
    return _ecvl.ResizeDim(src, dst, newdims, interp)


def ResizeScale(src, dst, scales, interp=InterpolationType.linear):
    return _ecvl.ResizeScale(src, dst, scales, interp)


def Flip2D(src, dst):
    return _ecvl.Flip2D(src, dst)


def Mirror2D(src, dst):
    return _ecvl.Mirror2D(src, dst)


def Rotate2D(src, dst, angle, center=None, scale=1.0,
             interp=InterpolationType.linear):
    if center is None:
        center = []
    return _ecvl.Rotate2D(src, dst, angle, center, scale, interp)


def RotateFullImage2D(src, dst, angle, scale=1.0,
                      interp=InterpolationType.linear):
    return _ecvl.RotateFullImage2D(src, dst, angle, scale, interp)


def ChangeColorSpace(src, dst, new_type):
    return _ecvl.ChangeColorSpace(src, dst, new_type)


def Threshold(src, dst, thresh, maxval, thresh_type=ThresholdingType.BINARY):
    return _ecvl.Threshold(src, dst, thresh, maxval, thresh_type)


def OtsuThreshold(src):
    return _ecvl.OtsuThreshold(src)


def Filter2D(src, dst, ker, type=DataType.none):
    return _ecvl.Filter2D(src, dst, ker, type)


def SeparableFilter2D(src, dst, kerX, kerY, type=DataType.none):
    return _ecvl.SeparableFilter2D(src, dst, kerX, kerY, type)


def GaussianBlur(src, dst, sizeX, sizeY, sigmaX, sigmaY=0):
    return _ecvl.GaussianBlur(src, dst, sizeX, sizeY, sigmaX, sigmaY)


def GaussianBlur2(src, dst, sigma):
    return _ecvl.GaussianBlur(src, dst, sigma)


def AdditiveLaplaceNoise(src, dst, std_dev):
    return _ecvl.AdditiveLaplaceNoise(src, dst, std_dev)


def AdditivePoissonNoise(src, dst, lambda_):
    return _ecvl.AdditivePoissonNoise(src, dst, lambda_)


def GammaContrast(src, dst, gamma):
    return _ecvl.GammaContrast(src, dst, gamma)


def CoarseDropout(src, dst, p, drop_size, per_channel):
    return _ecvl.CoarseDropout(src, dst, p, drop_size, per_channel)


def IntegralImage(src, dst, dst_type=DataType.float64):
    return _ecvl.IntegralImage(src, dst, dst_type)


def NonMaximaSuppression(src, dst):
    return _ecvl.NonMaximaSuppression(src, dst)


def GetMaxN(src, n):
    return _ecvl.GetMaxN(src, n)


def ConnectedComponentsLabeling(src, dst):
    return _ecvl.ConnectedComponentsLabeling(src, dst)


def FindContours(src):
    return _ecvl.FindContours(src)


def Stack(src, dst):
    return _ecvl.Stack(src, dst)


def HConcat(src, dst):
    return _ecvl.HConcat(src, dst)


def VConcat(src, dst):
    return _ecvl.VConcat(src, dst)


def Morphology(src, dst, op, kernel, anchor=None, iterations=1, borderType=1,
               borderValue=0):
    if anchor is None:
        anchor = [-1, -1]
    return _ecvl.Morphology(src, dst, op, kernel, anchor, iterations,
                            borderType, borderValue)


def Inpaint(src, dst, inpaintMask, inpaintRadius,
            flag=InpaintTypes.INPAINT_TELEA):
    return _ecvl.Inpaint(src, dst, inpaintMask, inpaintRadius, flag)


def MeanStdDev(src):
    return _ecvl.MeanStdDev(src)


# == dataset_parser ==

class SplitType(_ecvl.SplitType):
    pass


class Sample(_ecvl.Sample):
    pass


class Split(_ecvl.Split):
    pass


class Dataset(_ecvl.Dataset):
    pass


# == augmentations ==

class AugmentationParam(_ecvl.AugmentationParam):
    pass


class Augmentation(_ecvl.Augmentation):
    pass


class SequentialAugmentationContainer(_ecvl.SequentialAugmentationContainer):
    pass


class AugRotate(_ecvl.AugRotate):
    pass


class AugResizeDim(_ecvl.AugResizeDim):
    pass


class AugResizeScale(_ecvl.AugResizeScale):
    pass


class AugFlip(_ecvl.AugFlip):
    pass


class AugMirror(_ecvl.AugMirror):
    pass


class AugGaussianBlur(_ecvl.AugGaussianBlur):
    pass


class AugAdditiveLaplaceNoise(_ecvl.AugAdditiveLaplaceNoise):
    pass


class AugAdditivePoissonNoise(_ecvl.AugAdditivePoissonNoise):
    pass


class AugGammaContrast(_ecvl.AugGammaContrast):
    pass


class AugCoarseDropout(_ecvl.AugCoarseDropout):
    pass


# == support_imgcodecs ==

class ImReadMode(_ecvl.ImReadMode):
    pass


def ImRead(filename, flags=ImReadMode.COLOR):
    return _ecvl.ImRead(filename, flags)


def ImWrite(filename, src):
    return _ecvl.ImWrite(filename, src)


# == support_eddl ==

class DatasetAugmentations(_ecvl.DatasetAugmentations):
    pass


class DLDataset(_ecvl.DLDataset):
    pass


def ImageToTensor(img, offset=None):
    if offset is None:
        return _ecvl.ImageToTensor(img)
    return _ecvl.ImageToTensor(img, offset)


def TensorToImage(t):
    return _ecvl.TensorToImage(t)


def TensorToView(t):
    return _ecvl.TensorToView(t)


# == support_openslide ==

def OpenSlideGetLevels(filename):
    return _ecvl.OpenSlideGetLevels(filename)


def OpenSlideRead(filename, level, dims):
    return _ecvl.OpenSlideRead(filename, level, dims)


# == support_nifti ==

def NiftiRead(filename):
    return _ecvl.NiftiRead(filename)


def NiftiWrite(filename, src):
    return _ecvl.NiftiWrite(filename, src)


# == support_dcmtk ==

def DicomRead(filename):
    return _ecvl.DicomRead(filename)


def DicomWrite(filename, src):
    return _ecvl.DicomWrite(filename, src)


# == dataset_generator ==

# FIXME: these cannot be extended. Probably a missing trampoline class.

GenerateSegmentationDataset = _ecvl.GenerateSegmentationDataset

GenerateClassificationDataset = _ecvl.GenerateClassificationDataset
