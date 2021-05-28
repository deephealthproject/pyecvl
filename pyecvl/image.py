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


__all__ = [
    "ColorType",
    "Device",
    "Image",
    "View_int8",
    "View_int16",
    "View_float32",
    "CopyImage",
    "ShallowCopyImage",
    "RearrangeChannels",
    "ConvertTo",
]


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


class Device(_ecvl.Device):
    """\
    Enum class representing the supported devices.
    """
    NONE = _ecvl.Device.NONE
    CPU = _ecvl.Device.CPU
    GPU = _ecvl.Device.GPU
    FPGA = _ecvl.Device.FPGA


class Image(_ecvl.Image):
    r"""\
    Image class.

    :var elemtype\_: image pixel type, a DataType

    :var elemsize\_: image pixel size in bytes

    :dims\_: image dimensions in pixels/voxels (list of integers)

    :strides\_: the number of bytes the internal data pointer has to skip to
      get to the next pixel/voxel in the corresponding dimension

    :var channels\_: a string describing the image planes layout. Each
      character provides information on the corresponding channel. The
      possible values are: 'x': horizontal spatial dimension; 'y': vertical
      spatial dimension; 'z': depth spatial dimension; 'c': color dimension;
      't': temporal dimension; 'o': any other dimension. For example, "xyc"
      describes a 2-dimensional image structured in color planes. This could
      be for example a ColorType.GRAY Image with dims\_[2] = 1 or a
      ColorType.RGB Image with dims_[2] = 3. The ColorType constrains the
      value of the dimension corresponding to the color channel. Another
      example is "cxy" with dims\_[0] = 3 and ColorType.BGR. In this case the
      color dimension is the one which changes faster, as it happens in
      libraries such as OpenCV.

    :var colortype\_: image ColorType. If different from ColorType.none, the
      channels\_ string must contain a 'c' and the corresponding dimension must
      have the appropriate value.

    :var spacings\_: space in mm between consecutive pixels/voxels on each
      axis (list of floats).

    :var datasize\_: size of image data in bytes.

    :var contiguous\_: whether the image is stored contiguously in memory

    :var dev\_: image Device
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

    def __init__(self, dims, elemtype, channels, colortype, spacings=None,
                 dev=Device.CPU):
        """\
        :param dims: image dimensions
        :param elemtype: pixel type, a DataType
        :param channels: channels string
        :param colortype: a ColorType
        :param spacings: spacings between pixels
        :param dev: image Device
        """
        if spacings is None:
            spacings = []
        _ecvl.Image.__init__(
            self, dims, elemtype, channels, colortype, spacings, dev
        )

    def copy(self):
        """\
        Create a deep copy of this image.

        :return: a copy of this image
        """
        return _ecvl.Image(self)

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

    def Width(self):
        """\
        Get the image width.

        :return: image width
        """
        return _ecvl.Image.Width(self)

    def Height(self):
        """\
        Get the image height.

        :return: image height
        """
        return _ecvl.Image.Height(self)

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

    def To(self, dev):
        """\
        Change the image device.

        :param dev: new Device
        :return: None
        """
        return _ecvl.Image.To(self, dev)

    def ConvertTo(self, dtype, saturate=True):
        """\
        Convert Image to another DataType.

        :param dtype: target DataType
        :param saturate: whether to apply saturation or not
        """
        return _ecvl.Image.ConvertTo(self, dtype, saturate)


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


def ShallowCopyImage(src, dst):
    """\
    Shallow copy of ``src`` to ``dst`` (``dst`` will point to the same data).

    ``src`` and ``dst`` cannot be the same image. Even though ``dst`` will
    point to the same data as ``src``, the latter will be the data owner.

    :param src: source image
    :param dst: destination image
    :return: None
    """
    return _ecvl.ShallowCopyImage(src, dst)


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


def ConvertTo(src, dst, dtype, saturate=True):
    """\
    Convert Image to another DataType.

    :param src: source image
    :param dst: destination image
    :param dtype: target DataType
    :param saturate: whether to apply saturation or not
    """
    return _ecvl.ConvertTo(src, dst, dtype, saturate)
