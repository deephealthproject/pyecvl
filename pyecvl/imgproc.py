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

from .datatype import DataType
from . import _core
_ecvl = _core.ecvl


__all__ = [
    "ThresholdingType",
    "InterpolationType",
    "MorphType",
    "InpaintType",
    "BorderType",
    "ResizeDim",
    "ResizeScale",
    "Flip2D",
    "Mirror2D",
    "Rotate2D",
    "RotateFullImage2D",
    "ChangeColorSpace",
    "Threshold",
    "MultiThreshold",
    "OtsuThreshold",
    "OtsuMultiThreshold",
    "Filter2D",
    "SeparableFilter2D",
    "GaussianBlur",
    "GaussianBlur2",
    "AdditiveLaplaceNoise",
    "AdditivePoissonNoise",
    "GammaContrast",
    "CoarseDropout",
    "IntegralImage",
    "NonMaximaSuppression",
    "GetMaxN",
    "ConnectedComponentsLabeling",
    "FindContours",
    "Stack",
    "HConcat",
    "VConcat",
    "Morphology",
    "Inpaint",
    "MeanStdDev",
    "Transpose",
    "GridDistortion",
    "ElasticTransform",
    "OpticalDistortion",
    "Salt",
    "Pepper",
    "SaltAndPepper",
    "SliceTimingCorrection",
    "Moments",
    "CentralMoments",
    "DrawEllipse",
    "DropColorChannel",
    "Normalize",
    "CenterCrop",
    "ScaleTo",
    "Pad",
    "RandomCrop",
]


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


class MorphType(_ecvl.MorphType):
    """\
    Enum class representing the possible morph types.
    """
    MORPH_ERODE = _ecvl.MorphType.MORPH_ERODE
    MORPH_DILATE = _ecvl.MorphType.MORPH_DILATE
    MORPH_OPEN = _ecvl.MorphType.MORPH_OPEN
    MORPH_CLOSE = _ecvl.MorphType.MORPH_CLOSE
    MORPH_GRADIENT = _ecvl.MorphType.MORPH_GRADIENT
    MORPH_TOPHAT = _ecvl.MorphType.MORPH_TOPHAT
    MORPH_BLACKHAT = _ecvl.MorphType.MORPH_BLACKHAT
    MORPH_HITMISS = _ecvl.MorphType.MORPH_HITMISS


class InpaintType(_ecvl.InpaintType):
    """\
    Enum class representing the possible inpaint types.
    """
    INPAINT_NS = _ecvl.InpaintType.INPAINT_NS
    INPAINT_TELEA = _ecvl.InpaintType.INPAINT_TELEA


class BorderType(_ecvl.BorderType):
    """\
    Enum class representing the possible border types.
    """
    BORDER_CONSTANT = _ecvl.BorderType.BORDER_CONSTANT
    BORDER_REPLICATE = _ecvl.BorderType.BORDER_REPLICATE
    BORDER_REFLECT = _ecvl.BorderType.BORDER_REFLECT
    BORDER_WRAP = _ecvl.BorderType.BORDER_WRAP
    BORDER_REFLECT_101 = _ecvl.BorderType.BORDER_REFLECT_101
    BORDER_TRANSPARENT = _ecvl.BorderType.BORDER_TRANSPARENT


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


def MultiThreshold(src, dst, thresholds, minval=0, maxval=255):
    """\
    Apply multiple thresholds to an image.

    The resulting image is quantized based on the provided ``thresholds``
    values. Output values will range uniformly from ``minval`` to ``maxval``.

    :param src: source image
    :param dst: destination image
    :param thresh: threshold values
    :param maxval: minimum value in the output image
    :param maxval: maximum value in the output image
    :return: None
    """
    return _ecvl.MultiThreshold(src, dst, thresholds, minval, maxval)


def OtsuThreshold(src):
    """\
    Calculate the Otsu thresholding value.

    The image must be ColorType.GRAY.

    :param src: source image
    :return: Otsu threshold value
    """
    return _ecvl.OtsuThreshold(src)


def OtsuMultiThreshold(src, n_thresholds=2):
    """\
    Calculate the Otsu thresholding values.

    The image must be ColorType.GRAY. The number of thresholds to be found is
    defined by the n_thresholds parameter (default is 2).

    :param src: source image
    :return: Otsu threshold values (list of integers)
    """
    return _ecvl.OtsuMultiThreshold(src, n_thresholds)


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
    :return: number of different objects, including the background
    """
    return _ecvl.ConnectedComponentsLabeling(src, dst)


def FindContours(src):
    """\
    Find contours in the input image.

    The ``src`` image must be "xyc", only one color channel and DataType.uint8.

    :param src: source image
    :return: image contours
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


def Morphology(src, dst, op, kernel, anchor=None, iterations=1,
               border_type=BorderType.BORDER_CONSTANT, border_value=0):
    """\
    Perform morphological transformations based on erosion and dilation.

    :param src: input image
    :param dst: output image
    :param op: a MorphType
    :param kernel: structuring element
    :param anchor: anchor position within the kernel. A negative value means
      that the anchor is at the center of the kernel
    :param iterations: number of times erosion and dilation are applied
    :param border_type: pixel extrapolation method, see BorderType.
      BorderType.BORDER_WRAP is not supported
    :param borderValue: border value in case of a constant border
    :return: None
    """
    if anchor is None:
        anchor = [-1, -1]
    return _ecvl.Morphology(src, dst, op, kernel, anchor, iterations,
                            border_type, border_value)


def Inpaint(src, dst, inpaintMask, inpaintRadius,
            flag=InpaintType.INPAINT_TELEA):
    """\
    Restore a region in an image using the region's neighborhood.

    :param src: input image
    :param dst: output image
    :param inpaintMask: an Image with 1 channel and DataType.uint8. Non-zero
      pixels indicate the area that needs to be inpainted.
    :param inpaintRadius: radius of a circular neighborhood of each point
      inpainted that is considered by the algorithm.
    :param flag: inpainting method (an InpaintType)
    :return: None
    """
    return _ecvl.Inpaint(src, dst, inpaintMask, inpaintRadius, flag)


def MeanStdDev(src):
    """\
    Calculate the mean and the standard deviation of an image.

    :param src: input image
    :return: a (mean, stddev) tuple
    """
    return _ecvl.MeanStdDev(src)


def Transpose(src, dst):
    """\
    Swap rows and columns of an image.

    :param src: input image
    :param dst: output image
    :return: None
    """
    return _ecvl.Transpose(src, dst)


def GridDistortion(src, dst, num_steps=5, distort_limit=None,
                   interp=InterpolationType.linear,
                   border_type=BorderType.BORDER_REFLECT_101, border_value=0,
                   seed=None):
    """\
    Divide the image into a cell grid and randomly stretch or reduce each cell.

    :param src: input image
    :param dst: output image
    :param num_steps: grid cell count on each side
    :param distort_limit: distortion steps range
    :param interp: InterpolationType to be used
    :param border_type: pixel extrapolation method, see BorderType
    :param border_value: padding value if border_type is
      BorderType.BORDER_CONSTANT
    :param seed: seed for the random number generator
    :return: None
    """
    if distort_limit is None:
        distort_limit = [-0.3, 0.3]
    if seed is None:
        return _ecvl.GridDistortion(src, dst, num_steps, distort_limit,
                                    interp, border_type, border_value)
    return _ecvl.GridDistortion(src, dst, num_steps, distort_limit,
                                interp, border_type, border_value, seed)


def ElasticTransform(src, dst, alpha=34, sigma=4,
                     interp=InterpolationType.linear,
                     border_type=BorderType.BORDER_REFLECT_101,
                     border_value=0, seed=None):
    """\
    Elastic deformation of input image.

    :param src: input image
    :param dst: output image
    :param alpha: scaling factor that controls the intensity of the deformation
    :param sigma: Gaussian kernel standard deviation
    :param interp: InterpolationType to be used. If ``src`` is DataType.int8
      or DataType.int32, InterpolationType.nearest is used
    :param border_type: pixel extrapolation method, see BorderType
    :param border_value: padding value if border_type is
      BorderType.BORDER_CONSTANT
    :param seed: seed for the random number generator
    :return: None
    """
    if seed is None:
        return _ecvl.ElasticTransform(src, dst, alpha, sigma, interp,
                                      border_type, border_value)
    return _ecvl.ElasticTransform(src, dst, alpha, sigma, interp, border_type,
                                  border_value, seed)


def OpticalDistortion(src, dst, distort_limit=None, shift_limit=None,
                      interp=InterpolationType.linear,
                      border_type=BorderType.BORDER_REFLECT_101,
                      border_value=0, seed=None):
    """\
    Barrel / pincushion distortion.

    :param src: input image
    :param dst: output image
    :param distort_limit: distortion intensity range
    :param shift_limit: image shifting range
    :param interp: InterpolationType to be used
    :param border_type: pixel extrapolation method, see BorderType
    :param border_value: padding value if border_type is
      BorderType.BORDER_CONSTANT
    :param seed: seed for the random number generator
    :return: None
    """
    if distort_limit is None:
        distort_limit = [-0.3, 0.3]
    if shift_limit is None:
        shift_limit = [-0.1, 0.1]
    if seed is None:
        return _ecvl.OpticalDistortion(src, dst, distort_limit, shift_limit,
                                       interp, border_type, border_value)
    return _ecvl.OpticalDistortion(src, dst, distort_limit, shift_limit,
                                   interp, border_type, border_value, seed)


def Salt(src, dst, p, per_channel=False, seed=None):
    """\
    Add salt noise (white pixels) to the input image.

    :param src: input image
    :param dst: output image
    :param p: probability of replacing a pixel with salt noise
    :param per_channel: if True, apply channel-wide noise
    :param seed: seed for the random number generator
    :return: None
    """
    if seed is None:
        return _ecvl.Salt(src, dst, p, per_channel)
    return _ecvl.Salt(src, dst, p, per_channel, seed)


def Pepper(src, dst, p, per_channel=False, seed=None):
    """\
    Add pepper noise (black pixels) to the input image.

    :param src: input image
    :param dst: output image
    :param p: probability of replacing a pixel with pepper noise
    :param per_channel: if True, apply channel-wide noise
    :param seed: seed for the random number generator
    :return: None
    """
    if seed is None:
        return _ecvl.Pepper(src, dst, p, per_channel)
    return _ecvl.Pepper(src, dst, p, per_channel, seed)


def SaltAndPepper(src, dst, p, per_channel=False, seed=None):
    """\
    Add salt and pepper noise (white and black pixels) to the input image.

    White and black pixels are equally likely.

    :param src: input image
    :param dst: output image
    :param p: probability of replacing a pixel with salt or pepper noise
    :param per_channel: if True, apply channel-wide noise
    :param seed: seed for the random number generator
    :return: None
    """
    if seed is None:
        return _ecvl.SaltAndPepper(src, dst, p, per_channel)
    return _ecvl.SaltAndPepper(src, dst, p, per_channel, seed)


def SliceTimingCorrection(src, dst, odd=False, down=False):
    """\
    Correct each voxel's time-series.

    Slice timing correction works by using (Hanning-windowed) sinc
    interpolation to shift each time-series by an appropriate fraction of a TR
    relative to the middle of the TR period. The default slice order
    acquisition is from the bottom of the brain to the top.

    :param src: input image. Channels must be ``"xyzt"`` and the image must
      have spacings (distance between consecutive voxels on each dimension)
    :param dst: output image
    :param odd: True if odd slices were acquired with interleaved order
      ``(0, 2, 4, ..., 1, 3, 5, ...)``
    :param down: True if down slices were acquired from the top of the brain
      to the bottom
    """
    return _ecvl.SliceTimingCorrection(src, dst, odd, down)


def Moments(src, dst, order=3, type_=DataType.float64):
    """\
    Calculate raw image moments of the source image up to the specified order.

    Moments are stored in the output image in the same order as for source
    channels. The output image will be on the same device as the source image.

    :param src: input image. It must be a grayscale (ColorType.GRAY) or a
      data (ColorType.none) image.
    :param dst: output image (ColorType.none) containing the computed raw
      image moments. The size of the Image will be (order + 1, order + 1)
    :param order: moments order
    :param type_: data type for the output image

    """
    return _ecvl.Moments(src, dst, order, type_)


def CentralMoments(src, moments, center, order=3, type_=DataType.float64):
    """\
    Calculate central moments of the source image up to the specified order.

    :param src: input image. It must be a grayscale (ColorType.GRAY) or a
      data (ColorType.none) image.
    :param moments: output data (ColorType.none) image containing the computed
      moments. The size of the Image will be (order + 1, order + 1)
    :param center: center coordinates (list of floats) ``len(center)`` and
      ``src.dims_`` must match. The source axes order must be the same used to
      specify the center coordinates.
    :param order: moments order
    :param type_: data type for the output image
    """
    return _ecvl.CentralMoments(src, moments, center, order, type_)


def DrawEllipse(src, center, axes, angle, color, thickness=1):
    """\
    Draw an ellipse over the specified Image.

    :param src: input (and output) image.
    :param center: center of the ellipse
    :param axes: ellipse axes half size
    :param angle: rotation angle of the ellipse
    :param color: ellipse color, e.g., ``[255]``, ``[5, 5, 5]`` (RGB)
    :param thickness: ellipse border thickness. If negative all the pixels of
      the ellipse will be filled with the specified color value.
    """
    return _ecvl.DrawEllipse(src, center, axes, angle, color, thickness)


def DropColorChannel(src):
    """\
    Remove color channel from the input image.

    Remove the color channel ("c") from the specified input image, modifying
    all other attributes accordingly. This function can only be applied to
    images with ``ColorType.GRAY``, i.e., having the color channel dimension
    equal to 1.

    :param src: input image.
    """
    return _ecvl.DropColorChannel(src)


def Normalize(src, dst, mean, std):
    """\
    Normalize the input image with mean and standard deviation.

    For each pixel, subtract mean and divide by std. Useful to normalize a
    dataset, getting the data within a range.

    For xyc input images, ``mean`` and ``std`` can be lists of floats,
    representing separate mean and standard deviation for each color channel.

    :param src: input image.
    :param dst: output image.
    :param mean: mean to use for normalization.
    :param std: standard deviation to use for normalization.
    """
    return _ecvl.Normalize(src, dst, mean, std)


def CenterCrop(src, dst, size):
    """\
    Crop the given image at the center.

    :param src: input image.
    :param dst: output image.
    :param size: list of integers [w, h] specifying the desired output size
    """
    return _ecvl.CenterCrop(src, dst, size)


def ScaleTo(src, dst, new_min, new_max):
    """\
    Linearly scale an Image to a new range.

    :param src: input image.
    :param dst: output image.
    :param new_min: new minimum value
    :param new_max: new maximum value
    """
    return _ecvl.ScaleTo(src, dst, new_min, new_max)


def Pad(src, dst, padding, border_type=BorderType.BORDER_CONSTANT, border_value=0):
    """\
    Pad an Image.

    Add a border to the four sides of the image. It can be specified equal
    for all the sides, equal for top and bottom and for left and right or
    different for all the sides.

    :param src: input image
    :param dst: output image
    :param padding: list of integers representing the border sizes. It can
      have one element (same padding for all sides), two elements (top/bottom,
      left/right) or four (top, bottom, left, right)
    :param border_type: a BorderType
    :param border_value: pixel value for the border if ``border_type`` is
      ``BORDER_CONSTANT``
    """
    return _ecvl.Pad(src, dst, padding, border_type, border_value)


def RandomCrop(src, dst, size, pad_if_needed=False, border_type=BorderType.BORDER_CONSTANT,
               border_value=0, seed=None):
    """\
    Crop the source Image to the specified size at a random location.

    :param src: input image.
    :param dst: output image.
    :param size: list of intergers representing the desired (width, height) of
      the output Image.
    :param pad_if_needed: if the desired size is bigger than the src image and
      ``pad_if_needed`` is True, pad the image; otherwise, throw an exception.
    :param border_type: BorderType to use if ```pad_if_needed`` is True.
    :param border_value: pixel value for the border if ``border_type`` is
      ``BORDER_CONSTANT`` and ``pad_if_needed`` is True.
    """
    if seed is None:
        return _ecvl.RandomCrop(src, dst, size, pad_if_needed, border_type, border_value)
    return _ecvl.RandomCrop(src, dst, size, pad_if_needed, border_type, border_value, seed)
