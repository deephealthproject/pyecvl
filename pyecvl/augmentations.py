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

from .imgproc import InterpolationType, BorderType
from . import _core
_ecvl = _core.ecvl


if not _ecvl.ECVL_EDDL:
    raise ImportError("extension module not compiled with EDDL support")


__all__ = [
    "AugmentationParam",
    "AugmentationFactory",
    "SequentialAugmentationContainer",
    "OneOfAugmentationContainer",
    "AugRotate",
    "AugResizeDim",
    "AugResizeScale",
    "AugFlip",
    "AugMirror",
    "AugGaussianBlur",
    "AugAdditiveLaplaceNoise",
    "AugAdditivePoissonNoise",
    "AugGammaContrast",
    "AugCoarseDropout",
    "AugTranspose",
    "AugBrightness",
    "AugGridDistortion",
    "AugElasticTransform",
    "AugOpticalDistortion",
    "AugSalt",
    "AugPepper",
    "AugSaltAndPepper",
    "AugNormalize",
    "AugCenterCrop",
    "AugToFloat32",
    "AugDivBy255",
    "AugScaleTo",
    "AugRandomCrop",
]


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


class AugmentationFactory(_ecvl.AugmentationFactory):
    r"""\
    Creates augmentations from text strings.

    If only one argument is supplied, it needs to include the augmentation's
    name, e.g.::

        AugmentationFactory.create('AugFlip p=0.5')

    If only two arguments are supplied, the first is the augmentation's
    name, e.g.::

        AugmentationFactory.create('AugFlip', 'p=0.5')
    """

    @staticmethod
    def create(s1, s2=None):
        if s2 is None:
            return _ecvl.AugmentationFactory.create(s1)
        return _ecvl.AugmentationFactory.create(s1, s2)


class SequentialAugmentationContainer(_ecvl.SequentialAugmentationContainer):
    """\
    A container for multiple augmentations to be applied in sequence.
    """

    @staticmethod
    def fromtext(txt):
        r"""\
        Create a SequentialAugmentationContainer from a text description,
        e.g.::

            txt = '''\
            AugFlip p=0.2
            AugMirror p=0.4
            end
            '''
            c = SequentialAugmentationContainer(txt)
        """
        return _ecvl.SequentialAugmentationContainer(txt)

    def __init__(self, augs):
        """\
        :param augs: list of augmentations to be applied
        """
        _ecvl.SequentialAugmentationContainer.__init__(self, augs)


class OneOfAugmentationContainer(_ecvl.OneOfAugmentationContainer):
    """\
    A container for multiple augmentations, from which one is randomly chosen.

    The chosen augmentation will be applied with a user-specified probability.
    """

    @staticmethod
    def fromtext(txt):
        r"""\
        Create a OneOfAugmentationContainer from a text description,
        e.g.::

            txt = '''\
            p=0.7
            AugFlip p=0.2
            AugMirror p=0.4
            end
            '''
            c = OneOfAugmentationContainer(txt)
        """
        return _ecvl.OneOfAugmentationContainer(txt)

    def __init__(self, p, augs):
        """\
        :param p: probability of applying the chosen augmentation
        :param augs: list of augmentations
        """
        _ecvl.OneOfAugmentationContainer.__init__(self, p, augs)


class AugRotate(_ecvl.AugRotate):
    """\
    Augmentation wrapper for Rotate2D.
    """

    @staticmethod
    def fromtext(txt):
        r"""\
        Create an AugRotate from a text description, e.g.::

            a = AugRotate('angle=[30, 50] center=(2, 3) '
                          'scale=1.1 interp="nearest"')
        """
        return _ecvl.AugRotate(txt)

    def __init__(self, angle, center=None, scale=1.0,
                 interp=InterpolationType.linear,
                 gt_interp=InterpolationType.nearest):
        """\
        :param angle: range of degrees ``[min, max]`` to randomly select from
        :param center: a list of floats representing the coordinates of the
          rotation center. If None, the center of the image is used
        :param scale: scaling factor
        :param interp: InterpolationType to be used
        :param gt_interp: InterpolationType to be used for ground truth
        """
        if center is None:
            center = []
        _ecvl.AugRotate.__init__(self, angle, center, scale, interp)


class AugResizeDim(_ecvl.AugResizeDim):
    """\
    Augmentation wrapper for ResizeDim.
    """

    @staticmethod
    def fromtext(txt):
        r"""\
        Create an AugResizeDim from a text description, e.g.::

            a = AugResizeDim('dims=(4, 3) interp="linear"')
        """
        return _ecvl.AugResizeDim(txt)

    def __init__(self, dims, interp=InterpolationType.linear,
                 gt_interp=InterpolationType.nearest):
        """\
        :param dims: list of integers that specifies the new size of each
          dimension
        :param interp: InterpolationType to be used
        :param gt_interp: InterpolationType to be used for ground truth
        """
        _ecvl.AugResizeDim.__init__(self, dims, interp)


class AugResizeScale(_ecvl.AugResizeScale):
    """\
    Augmentation wrapper for ResizeScale.
    """

    @staticmethod
    def fromtext(txt):
        r"""\
        Create an AugResizeScale from a text description, e.g.::

            a = AugResizeScale('scale=(0.5, 0.5) interp="linear"')
        """
        return _ecvl.AugResizeScale(txt)

    def __init__(self, scale, interp=InterpolationType.linear,
                 gt_interp=InterpolationType.nearest):
        """\
        :param scale: list of floats that specifies the scale to apply to
          each dimension
        :param interp: InterpolationType to be used
        :param gt_interp: InterpolationType to be used for ground truth
        """
        _ecvl.AugResizeScale.__init__(self, scale, interp)


class AugFlip(_ecvl.AugFlip):
    """\
    Augmentation wrapper for Flip2D.
    """

    @staticmethod
    def fromtext(txt):
        r"""\
        Create an AugFlip from a text description, e.g.::

            a = AugFlip('p=0.5')
        """
        return _ecvl.AugFlip(txt)

    def __init__(self, p=0.5):
        """\
        :param p: probability of each image to get flipped
        """
        _ecvl.AugFlip.__init__(self, p)


class AugMirror(_ecvl.AugMirror):
    """\
    Augmentation wrapper for Mirror2D.
    """

    @staticmethod
    def fromtext(txt):
        r"""\
        Create an AugMirror from a text description, e.g.::

            a = AugMirror('p=0.5')
        """
        return _ecvl.AugMirror(txt)

    def __init__(self, p=0.5):
        """\
        :param p: probability of each image to get mirrored
        """
        _ecvl.AugMirror.__init__(self, p)


class AugGaussianBlur(_ecvl.AugGaussianBlur):
    """\
    Augmentation wrapper for GaussianBlur.
    """

    @staticmethod
    def fromtext(txt):
        r"""\
        Create an AugGaussianBlur from a text description, e.g.::

            a = AugGaussianBlur('sigma=[0.2, 0.4]')
        """
        return _ecvl.AugGaussianBlur(txt)

    def __init__(self, sigma):
        """\
        :param sigma: sigma range ``[min, max]`` to randomly select from.
        """
        _ecvl.AugGaussianBlur.__init__(self, sigma)


class AugAdditiveLaplaceNoise(_ecvl.AugAdditiveLaplaceNoise):
    """\
    Augmentation wrapper for AdditiveLaplaceNoise.
    """

    @staticmethod
    def fromtext(txt):
        r"""\
        Create an AugAdditiveLaplaceNoise from a text description, e.g.::

            a = AugAdditiveLaplaceNoise('std_dev=[12.5, 23.1]')
        """
        return _ecvl.AugAdditiveLaplaceNoise(txt)

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

    @staticmethod
    def fromtext(txt):
        r"""\
        Create an AugAdditivePoissonNoise from a text description, e.g.::

            a = AugAdditivePoissonNoise('lambda=[2.0, 3.0]')
        """
        return _ecvl.AugAdditivePoissonNoise(txt)

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

    @staticmethod
    def fromtext(txt):
        r"""\
        Create an AugGammaContrast from a text description, e.g.::

            a = AugGammaContrast('gamma=[3, 4]')
        """
        return _ecvl.AugGammaContrast(txt)

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

    @staticmethod
    def fromtext(txt):
        r"""\
        Create an AugCoarseDropout from a text description, e.g.::

            a = AugCoarseDropout('p=[0.5, 0.7] drop_size=[0.1, 0.2] '
                                 'per_channel=0.4')
        """
        return _ecvl.AugCoarseDropout(txt)

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


class AugTranspose(_ecvl.AugTranspose):
    """\
    Augmentation wrapper for Transpose.
    """

    @staticmethod
    def fromtext(txt):
        r"""\
        Create an AugTranspose from a text description, e.g.::

            a = AugTranspose('p=0.5')
        """
        return _ecvl.AugTranspose(txt)

    def __init__(self, p=0.5):
        """\
        :param p: probability of each image to get transposed.
        """
        _ecvl.AugTranspose.__init__(self, p)


class AugBrightness(_ecvl.AugBrightness):
    """\
    Augmentation wrapper for brightness adjustment.
    """

    @staticmethod
    def fromtext(txt):
        r"""\
        Create an AugBrightness from a text description, e.g.::

            a = AugBrightness('beta=[30, 60]')
        """
        return _ecvl.AugBrightness(txt)

    def __init__(self, beta):
        """\
        :param beta: range of values ``[min, max]`` to randomly select from \
          for the brightness adjustment. Suggested values are around 0 to 100.
        """
        _ecvl.AugBrightness.__init__(self, beta)


class AugGridDistortion(_ecvl.AugGridDistortion):
    """\
    Augmentation wrapper for GridDistortion.
    """

    @staticmethod
    def fromtext(txt):
        r"""\
        Create an AugGridDistortion from a text description, e.g.::

            a = AugGridDistortion('num_steps=[5,10] distort_limit=[-0.2,0.2] '
                                  'interp=\"linear\" '
                                  'border_type=\"reflect_101\" '
                                  'border_value=0')
        """
        return _ecvl.AugGridDistortion(txt)

    def __init__(self, num_steps, distort_limit,
                 interp=InterpolationType.linear,
                 border_type=BorderType.BORDER_REFLECT_101, border_value=0):
        """\
        :param num_steps: range of values ``[min, max]`` to randomly select
          the number of grid cells on each side
        :param distort_limit: range of values ``[min, max]`` to randomly select
          the distortion steps
        :param interp: InterpolationType to be used
        :param border_type: pixel extrapolation method, see BorderType
        :param border_value: padding value if border_type is
          BorderType.BORDER_CONSTANT
        """
        _ecvl.AugGridDistortion.__init__(self, num_steps, distort_limit,
                                         interp, border_type, border_value)


class AugElasticTransform(_ecvl.AugElasticTransform):
    """\
    Augmentation wrapper for ElasticTransform.
    """

    @staticmethod
    def fromtext(txt):
        r"""\
        Create an AugElasticTransform from a text description, e.g.::

            a = AugElasticTransform('alpha=[34,60] sigma=[4,6] '
                                    'interp=\"linear\" '
                                    'border_type=\"reflect_101\" '
                                    'border_value=0')
        """
        return _ecvl.AugElasticTransform(txt)

    def __init__(self, alpha, sigma, interp=InterpolationType.linear,
                 border_type=BorderType.BORDER_REFLECT_101, border_value=0):
        """\
        :param alpha: range of values ``[min, max]`` to randomly select the
          scaling factor that controls the intensity of the deformation
        :param sigma: range of values ``[min, max]`` to randomly select the
          gaussian kernel standard deviation
        :param interp: InterpolationType to be used
        :param border_type: pixel extrapolation method, see BorderType
        :param border_value: padding value if border_type is
          BorderType.BORDER_CONSTANT
        """
        _ecvl.AugElasticTransform.__init__(self, alpha, sigma, interp,
                                           border_type, border_value)


class AugOpticalDistortion(_ecvl.AugOpticalDistortion):
    """\
    Augmentation wrapper for OpticalDistortion.
    """

    @staticmethod
    def fromtext(txt):
        r"""\
        Create an AugOpticalDistortion from a text description, e.g.::

            a = AugOpticalDistortion('distort_limit=[-0.2,0.2] '
                                     'shift_limit=[-0.4,0.4] '
                                     'interp=\"linear\" '
                                     'border_type=\"reflect_101\" '
                                     'border_value=0')
        """
        return _ecvl.AugOpticalDistortion(txt)

    def __init__(self, distort_limit, shift_limit,
                 interp=InterpolationType.linear,
                 border_type=BorderType.BORDER_REFLECT_101, border_value=0):
        """\
        :param distort_limit: range of values ``[min, max]`` to randomly select
          the distortion steps
        :param shift_limit: range of values ``[min, max]`` to randomly select
          the image shifting
        :param interp: InterpolationType to be used
        :param border_type: pixel extrapolation method, see BorderType
        :param border_value: padding value if border_type is
          BorderType.BORDER_CONSTANT
        """
        _ecvl.AugOpticalDistortion.__init__(self, distort_limit, shift_limit,
                                            interp, border_type, border_value)


class AugSalt(_ecvl.AugSalt):
    """\
    Augmentation wrapper for Salt.
    """

    @staticmethod
    def fromtext(txt):
        r"""\
        Create an AugSalt from a text description, e.g.::

            a = AugSalt('p=[0.1,0.3] per_channel=0.5')
        """
        return _ecvl.AugSalt(txt)

    def __init__(self, p, per_channel):
        """\
        :param p: range of values ``[min, max]`` for the probability of any
          pixel to be set to white
        :param per_channel: probability to use the same value for all channels
        """
        _ecvl.AugSalt.__init__(self, p, per_channel)


class AugPepper(_ecvl.AugPepper):
    """\
    Augmentation wrapper for Pepper.
    """

    @staticmethod
    def fromtext(txt):
        r"""\
        Create an AugPepper from a text description, e.g.::

            a = AugPepper('p=[0.1,0.3] per_channel=0.5')
        """
        return _ecvl.AugPepper(txt)

    def __init__(self, p, per_channel):
        """\
        :param p: range of values ``[min, max]`` for the probability of any
          pixel to be set to black
        :param per_channel: probability to use the same value for all channels
        """
        _ecvl.AugPepper.__init__(self, p, per_channel)


class AugSaltAndPepper(_ecvl.AugSaltAndPepper):
    """\
    Augmentation wrapper for SaltAndPepper.
    """

    @staticmethod
    def fromtext(txt):
        r"""\
        Create an AugSaltAndPepper from a text description, e.g.::

            a = AugSaltAndPepper('p=[0.1,0.3] per_channel=0.5')
        """
        return _ecvl.AugSaltAndPepper(txt)

    def __init__(self, p, per_channel):
        """\
        :param p: range of values ``[min, max]`` for the probability of any
          pixel to be set to white or black
        :param per_channel: probability to use the same value for all channels
        """
        _ecvl.AugSaltAndPepper.__init__(self, p, per_channel)


class AugNormalize(_ecvl.AugNormalize):
    """\
    Augmentation wrapper for Normalize.
    """

    @staticmethod
    def fromtext(txt):
        r"""\
        Create an AugNormalize from a text description, e.g.::

            a = AugNormalize('mean=20 std=5.5')

        Separate mean and std for xyc images::

            a = AugNormalize('mean=(20,19,21) std=(5,5.5,6)')
        """
        return _ecvl.AugNormalize(txt)

    def __init__(self, mean, std):
        """\
        For xyc input images, ``mean`` and ``std`` can be lists of floats,
        representing separate mean and standard deviation for each color
        channel.

        :param mean: mean to use for normalization
        :param std: standard deviation to use for normalization
        """
        _ecvl.AugNormalize.__init__(self, mean, std)


class AugCenterCrop(_ecvl.AugCenterCrop):
    """\
    Augmentation wrapper for CenterCrop.
    """

    @staticmethod
    def fromtext(txt):
        r"""\
        Create an AugCenterCrop from a text description, e.g.::

            a = AugCenterCrop('size=(10, 20)')
        """
        return _ecvl.AugCenterCrop(txt)

    def __init__(self, size=None):
        """\
        If size is ``None``, the crop size is inferred from the minimum
        image dimension.

        :param size: list of integers [w, h] specifying the output size
        """
        if size is None:
            _ecvl.AugCenterCrop.__init__(self)
        else:
            _ecvl.AugCenterCrop.__init__(self, size)


class AugToFloat32(_ecvl.AugToFloat32):
    """\
    Augmentation ToFloat32.

    Converts an Image (and ground truth) to DataType::float32 dividing it by
    divisor (or divisor_gt) parameter.
    """

    @staticmethod
    def fromtext(txt):
        r"""\
        Create an AugToFloat32 from a text description, e.g.::

            a = AugToFloat32('divisor=2. divisor_gt=3.')
        """
        return _ecvl.AugToFloat32(txt)

    def __init__(self, divisor=1., divisor_gt=1.):
        """\
        :param divisor: divisor for the image
        :param divisor: divisor for the ground truth
        """
        _ecvl.AugToFloat32.__init__(self, divisor, divisor_gt)


class AugDivBy255(_ecvl.AugDivBy255):
    """\
    Augmentation DivBy255.

    Divides an Image (and ground truth) by 255.
    """

    @staticmethod
    def fromtext(txt):
        r"""\
        Create an AugDivBy255 from a text description, e.g.::

            a = AugDivBy255('')
        """
        return _ecvl.AugDivBy255(txt)

    def __init__(self):
        """\
        """
        _ecvl.AugDivBy255.__init__(self)


class AugScaleTo(_ecvl.AugScaleTo):
    """\
    Augmentation wrapper for ScaleTo.
    """

    @staticmethod
    def fromtext(txt):
        r"""\
        Create an AugScaleTo from a text description, e.g.::

            a = AugScaleTo('new_min=1 new_max=255')
        """
        return _ecvl.AugScaleTo(txt)

    def __init__(self, new_min, new_max):
        """\
        :param new_min: new minimum value
        :param new_max: new maximum value
        """
        _ecvl.AugScaleTo.__init__(self, new_min, new_max)


class AugRandomCrop(_ecvl.AugRandomCrop):
    """\
    Augmentation wrapper for RandomCrop.
    """

    @staticmethod
    def fromtext(txt):
        r"""\
        Create an AugRandomCrop from a text description, e.g.::

            a = AugRandomCrop('size=(10, 20) border_type=\"constant\" border_value=0')
        """
        return _ecvl.AugRandomCrop(txt)

    def __init__(self, size, border_type=BorderType.BORDER_CONSTANT, border_value=0):
        """\
        :param size: list of integers [w, h] specifying the output size
        :param border_type: BorderType to use for pixel extrapolation if the
          desired size is bigger than the src image
        :param border_value: pixel value for the border if ``border_type`` is
          ``BORDER_CONSTANT``
        """
        if size is None:
            _ecvl.AugRandomCrop.__init__(self)
        else:
            _ecvl.AugRandomCrop.__init__(self, size)
