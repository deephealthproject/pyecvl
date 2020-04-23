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
    :param new_type: new DataType for the destination image. If None, the
      destination image will preserve its type if it is not empty, otherwise
      it will have the same type as the source image
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
    """\
    Enum class representing the possible thresholding types.
    """
    BINARY = _ecvl.ThresholdingType.BINARY
    BINARY_INV = _ecvl.ThresholdingType.BINARY_INV


class InterpolationType(_ecvl.InterpolationType):
    """\
    Enum class representing the possible interpolation types.
    """
    nearest = _ecvl.InterpolationType.nearest
    linear = _ecvl.InterpolationType.linear
    area = _ecvl.InterpolationType.area
    cubic = _ecvl.InterpolationType.cubic
    lanczos4 = _ecvl.InterpolationType.lanczos4


class MorphTypes(_ecvl.MorphTypes):
    """\
    Enum class representing the possible morph types.
    """
    MORPH_ERODE = _ecvl.MorphTypes.MORPH_ERODE
    MORPH_DILATE = _ecvl.MorphTypes.MORPH_DILATE
    MORPH_OPEN = _ecvl.MorphTypes.MORPH_OPEN
    MORPH_CLOSE = _ecvl.MorphTypes.MORPH_CLOSE
    MORPH_GRADIENT = _ecvl.MorphTypes.MORPH_GRADIENT
    MORPH_TOPHAT = _ecvl.MorphTypes.MORPH_TOPHAT
    MORPH_BLACKHAT = _ecvl.MorphTypes.MORPH_BLACKHAT
    MORPH_HITMISS = _ecvl.MorphTypes.MORPH_HITMISS


class InpaintTypes(_ecvl.InpaintTypes):
    """\
    Enum class representing the possible inpaint types.
    """
    INPAINT_NS = _ecvl.InpaintTypes.INPAINT_NS
    INPAINT_TELEA = _ecvl.InpaintTypes.INPAINT_TELEA


def ResizeDim(src, dst, newdims, interp=InterpolationType.linear):
    """\
    Resize an image to the specified dimensions.

    Resizes ``src`` and outputs the result in ``dst``.

    :param src: source image
    :param dst: destination image
    :param newdims: list of integers specifying the new size of each
      dimension. The lenght of the list must match the ``src`` image
      dimensions, excluding the color channel
    :param interp: InterpolationType to be used
    :return: None
    """
    return _ecvl.ResizeDim(src, dst, newdims, interp)


def ResizeScale(src, dst, scales, interp=InterpolationType.linear):
    """\
    Resize an image by scaling the dimensions by a given scale factor.

    Resizes ``src`` and outputs the result in ``dst``.

    :param src: source image
    :param dst: destination image
    :param scales: list of floats that specifies the scale to apply to each
      dimension. The length of the list must match the ``src`` image
      dimensions, excluding the color channel
    :param interp: InterpolationType to be used
    :return: None
    """
    return _ecvl.ResizeScale(src, dst, scales, interp)


def Flip2D(src, dst):
    """\
    Flip an image vertically.

    :param src: source image
    :param dst: destination image
    :return: None
    """
    return _ecvl.Flip2D(src, dst)


def Mirror2D(src, dst):
    """\
    Flip an image horizontally.

    :param src: source image
    :param dst: destination image
    :return: None
    """
    return _ecvl.Mirror2D(src, dst)


def Rotate2D(src, dst, angle, center=None, scale=1.0,
             interp=InterpolationType.linear):
    """\
    Rotate an image without changing its dimensions.

    Rotates an image clockwise by a given angle (in degrees), with respect to
    a given center. The values of unknown pixels in the output image are set
    to 0. The output image is guaranteed to have the same dimensions as the
    input one. An optional scale parameter can be provided: this won't change
    the output image size, but the image will be scaled during rotation.

    :param src: source image
    :param dst: destination image
    :param angle: the rotation angle in degrees
    :param center: a list of floats representing the coordinates of the
      rotation center. If None, the center of the image is used
    :param scale: scaling factor
    :param interp: InterpolationType to be used
    :return: None
    """
    if center is None:
        center = []
    return _ecvl.Rotate2D(src, dst, angle, center, scale, interp)


def RotateFullImage2D(src, dst, angle, scale=1.0,
                      interp=InterpolationType.linear):
    """\
    Rotate an image resizing the output to fit all the pixels.

    Rotates an image clockwise by a given angle (in degrees). The values of
    unknown pixels in the output image are set to 0. The output Image is
    guaranteed to contain all the pixels of the rotated image. Thus, its
    dimensions can be different from those of the input one. An optional scale
    parameter can be provided: if set, the image will also be scaled.

    :param src: source image
    :param dst: destination image
    :param angle: the rotation angle in degrees
    :param scale: scaling factor
    :param interp: InterpolationType to be used
    :return: None
    """
    return _ecvl.RotateFullImage2D(src, dst, angle, scale, interp)


def ChangeColorSpace(src, dst, new_type):
    """\
    Copy the ``src`` image into the ``dst`` image changing the color space.

    Source and destination can be the same image.

    :param src: source image
    :param dst: destination image
    :param new_type: a ColorType specifying the new color space
    :return: None
    """
    return _ecvl.ChangeColorSpace(src, dst, new_type)


def Threshold(src, dst, thresh, maxval, thresh_type=ThresholdingType.BINARY):
    """\
    Apply a fixed threshold to an image.

    This function can be used to get a binary image out of a grayscale
    (ColorType.GRAY) image or to remove noise, filtering out pixels with too
    small or too large values. Pixels up to the ``thresh`` value will be set
    to 0, others will be set to ``maxval`` if ``thresh_type`` is
    ThresholdingType.BINARY. The opposite will happen if ``thresh_type`` is
    set to ThresholdingType.BINARY_INV.

    :param src: source image
    :param dst: destination image
    :param thresh: threshold value
    :param maxval: maximum values in the thresholded image
    :param thresh_type: ThresholdingType to be applied
    :return: None
    """
    return _ecvl.Threshold(src, dst, thresh, maxval, thresh_type)


def OtsuThreshold(src):
    """\
    Calculate the Otsu thresholding value.

    The image must be ColorType.GRAY.

    :param src: source image
    :return: Otsu threshold value
    """
    return _ecvl.OtsuThreshold(src)


def Filter2D(src, dst, ker, type=DataType.none):
    """\
    Convolve an image with a kernel.

    :param src: source image
    :param dst: destination image
    :param ker: convolution kernel
    :param type: destination DataType. If set to DataType.none, the DataType
      of ``src`` is used
    :return: None
    """
    return _ecvl.Filter2D(src, dst, ker, type)


def SeparableFilter2D(src, dst, kerX, kerY, type=DataType.none):
    """\
    Convolve an image with a couple of 1-dimensional kernels.

    :param src: source image
    :param dst: destination image
    :param kerX: convolution kernel for the X axis.
    :param kerY: convolution kernel for the Y axis.
    :param type: destination DataType. If set to DataType.none, the DataType
      of ``src`` is used
    :return: None
    """
    return _ecvl.SeparableFilter2D(src, dst, kerX, kerY, type)


def GaussianBlur(src, dst, sizeX, sizeY, sigmaX, sigmaY=0):
    """\
    Blurs an image using a Gaussian kernel.

    :param src: source image
    :param dst: destination image
    :param sizeX: horizontal size of the kernel. Must be positive and odd
    :param sizeY: vertical size of the kernel. Must be positive and odd
    :param sigmaX: Gaussian kernel standard deviation in the X direction.
    :param sigmaY: Gaussian kernel standard deviation in the Y direction. If
      zero, sigmaX is used. If both are zero, they are calculated from sizeX
      and sizeY.
    :return: None
    """
    return _ecvl.GaussianBlur(src, dst, sizeX, sizeY, sigmaX, sigmaY)


def GaussianBlur2(src, dst, sigma):
    return _ecvl.GaussianBlur(src, dst, sigma)


def AdditiveLaplaceNoise(src, dst, std_dev):
    """\
    Adds Laplace distributed noise to an image.

    :param src: source image
    :param dst: destination image
    :param std_dev: standard deviation of the noise-generating distribution.
      Suggested values are around 255 * 0.05 for uint8 images
    :return: None
    """
    return _ecvl.AdditiveLaplaceNoise(src, dst, std_dev)


def AdditivePoissonNoise(src, dst, lambda_):
    r"""\
    Adds Poisson distributed noise to an image.

    :param src: source image
    :param dst: destination image
    :param lambda\_: lambda parameter of the Poisson distribution
    :return: None
    """
    return _ecvl.AdditivePoissonNoise(src, dst, lambda_)


def GammaContrast(src, dst, gamma):
    """\
    Adjust contrast by scaling each pixel value X to 255 * ((X/255) ** gamma).

    :param src: source image
    :param dst: destination image
    :param gamma: exponent for the contrast adjustment
    :return: None
    """
    return _ecvl.GammaContrast(src, dst, gamma)


def CoarseDropout(src, dst, p, drop_size, per_channel):
    """\
    Set rectangular areas within an image to zero.

    :param src: source image
    :param dst: destination image
    :param p: probability of any rectangle being set to zero
    :param drop_size: size of rectangles in percentage of the input image
    :param per_channel: whether to use the same value for all channels
    :return: None
    """
    return _ecvl.CoarseDropout(src, dst, p, drop_size, per_channel)


def IntegralImage(src, dst, dst_type=DataType.float64):
    """\
    Calculate the integral image of the source image.

    The ``src`` image must be ColorType.GRAY, "xyc" and DataType.uint8.

    :param src: source image
    :param dst: destination image
    :param dst_type: DataType of the destination image
    :return: None
    """
    return _ecvl.IntegralImage(src, dst, dst_type)


def NonMaximaSuppression(src, dst):
    """\
    Calculate the non-maxima suppression of the source image.

    The ``src`` image must be ColorType.GRAY, "xyc" and DataType.int32.

    :param src: source image
    :param dst: destination image
    :return: None
    """
    return _ecvl.NonMaximaSuppression(src, dst)


def GetMaxN(src, n):
    """\
    Get the indices of the ``n`` maximum values of an image.

    The ``src`` image must be ColorType.GRAY, "xyc" and DataType.int32.

    :param src: source image
    :param n: how many values to return
    :return: list of pairs corresponding to the coordinates of the max values
    """
    return _ecvl.GetMaxN(src, n)


def ConnectedComponentsLabeling(src, dst):
    """\
    Label connected components in the input image.

    The ``src`` image must be "xyc", only one color channel and DataType.uint8.

    :param src: source image
    :param dst: destination image
    :return: None
    """
    return _ecvl.ConnectedComponentsLabeling(src, dst)


def FindContours(src):
    """\
    Find contours in the input image.

    The ``src`` image must be "xyc", only one color channel and DataType.uint8.

    :param src: source image
    :param dst: destination image
    :return: None
    """
    return _ecvl.FindContours(src)


def Stack(src, dst):
    """\
    Stack a sequence of images along a new depth dimension.

    Images must be "xyc" and their dimensions must match.

    :param src: list of source images
    :param dst: destination image
    :return: None
    """
    return _ecvl.Stack(src, dst)


def HConcat(src, dst):
    """\
    Concatenate images horizontally.

    Images must be "xyc" and have the same number of rows.

    :param src: list of source images
    :param dst: destination image
    :return: None
    """
    return _ecvl.HConcat(src, dst)


def VConcat(src, dst):
    """\
    Concatenate images vertically.

    Images must be "xyc" and have the same number of columns.

    :param src: list of source images
    :param dst: destination image
    :return: None
    """
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


# == augmentations ==

class AugmentationParam(_ecvl.AugmentationParam):
    r"""\
    Augmentation parameters which must be randomly generated within a range.

    :var min\_: minimum value for the random range
    :var max\_: maximum value for the random range
    :var value\_: generated parameter value
    """
    def GenerateValue(self):
        r"""\
        Generate the random value between min\_ and max\_.
        """
        return _ecvl.AugmentationParam.GenerateValue(self)

    @staticmethod
    def SetSeed(seed):
        """\
        Set a fixed seed for the random generated values.

        Useful to reproduce experiments with same augmentations.

        :param seed: seed value
        :return: None
        """
        return _ecvl.AugmentationParam.SetSeed(seed)


class SequentialAugmentationContainer(_ecvl.SequentialAugmentationContainer):
    """\
    A container for multiple augmentations to be applied in sequence.
    """
    def __init__(self, augs):
        """\
        :param augs: list of augmentations to be applied
        """
        _ecvl.SequentialAugmentationContainer.__init__(self, augs)


class AugRotate(_ecvl.AugRotate):
    """\
    Augmentation wrapper for Rotate2D.
    """
    def __init__(self, angle, center=None, scale=1.0,
                 interp=InterpolationType.linear):
        """\
        :param angle: range of degrees ``[min, max]`` to randomly select from
        :param center: a list of floats representing the coordinates of the
          rotation center. If None, the center of the image is used
        :param scale: scaling factor
        :param interp: InterpolationType to be used
        """
        if center is None:
            center = []
        _ecvl.AugRotate.__init__(self, angle, center, scale, interp)


class AugResizeDim(_ecvl.AugResizeDim):
    """\
    Augmentation wrapper for ResizeDim.
    """
    def __init__(self, dims, interp=InterpolationType.linear):
        """\
        :param dims: list of integers that specifies the new size of each
          dimension
        :param interp: InterpolationType to be used
        """
        _ecvl.AugResizeDim.__init__(self, dims, interp)


class AugResizeScale(_ecvl.AugResizeScale):
    """\
    Augmentation wrapper for ResizeScale.
    """
    def __init__(self, scale, interp=InterpolationType.linear):
        """\
        :param scale: list of floats that specifies the scale to apply to
          each dimension
        :param interp: InterpolationType to be used
        """
        _ecvl.AugResizeScale.__init__(self, scale, interp)


class AugFlip(_ecvl.AugFlip):
    """\
    Augmentation wrapper for Flip2D.
    """
    def __init__(self, p=0.5):
        """\
        :param p: probability of each image to get flipped
        """
        _ecvl.AugFlip.__init__(self, p)


class AugMirror(_ecvl.AugMirror):
    """\
    Augmentation wrapper for Mirror2D.
    """
    def __init__(self, p=0.5):
        """\
        :param p: probability of each image to get mirrored
        """
        _ecvl.AugMirror.__init__(self, p)


class AugGaussianBlur(_ecvl.AugGaussianBlur):
    """\
    Augmentation wrapper for GaussianBlur.
    """
    def __init__(self, sigma):
        """\
        :param sigma: sigma range ``[min, max]`` to randomly select from.
        """
        _ecvl.AugGaussianBlur.__init__(self, sigma)


class AugAdditiveLaplaceNoise(_ecvl.AugAdditiveLaplaceNoise):
    """\
    Augmentation wrapper for AdditiveLaplaceNoise.
    """
    def __init__(self, std_dev):
        """\
        :param std_dev: range of values ``[min, max]`` to randomly select the \
          standard deviation of the noise generating distribution. Suggested \
          values are around 255 * 0.05 for uint8 images
        """
        _ecvl.AugAdditiveLaplaceNoise.__init__(self, std_dev)


class AugAdditivePoissonNoise(_ecvl.AugAdditivePoissonNoise):
    """\
    Augmentation wrapper for AdditivePoissonNoise.
    """
    def __init__(self, lambda_):
        """\
        :param lambda\_: range of values ``[min, max]`` to randomly select \
          the lambda of the noise generating distribution. Suggested values \
          are around 0.0 to 10.0.
        """  # noqa
        _ecvl.AugAdditivePoissonNoise.__init__(self, lambda_)


class AugGammaContrast(_ecvl.AugGammaContrast):
    """\
    Augmentation wrapper for GammaContrast.
    """
    def __init__(self, gamma):
        """\
        :param gamma: range of values ``[min, max]`` to randomly select the \
          exponent for the contrast adjustment. Suggested values are around \
          0.5 to 2.0.
        """
        _ecvl.AugGammaContrast.__init__(self, gamma)


class AugCoarseDropout(_ecvl.AugCoarseDropout):
    """\
    Augmentation wrapper for CoarseDropout.
    """
    def __init__(self, p, drop_size, per_channel):
        """\
        :param p: range of values ``[min, max]`` to randomly select the
          probability of any rectangle being set to zero
        :param drop_size: range of values ``[min, max]`` to randomly select
          the size of rectangles in percentage of the input image
        :param per_channel: probability of each image to use the same value
          for all channels of a pixel
        """
        _ecvl.AugCoarseDropout.__init__(self, p, drop_size, per_channel)


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
