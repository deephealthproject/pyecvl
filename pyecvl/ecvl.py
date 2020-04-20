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
    pass


def DataTypeSize(dt=None):
    if dt is None:
        return _ecvl.DataTypeSize()
    return _ecvl.DataTypeSize(dt)


def DataTypeSignedSize():
    return _ecvl.DataTypeSignedSize()


# == image ==

class ColorType(_ecvl.ColorType):
    pass


class Image(_ecvl.Image):
    pass


class View_int8(_ecvl.View_int8):
    pass


class View_int16(_ecvl.View_int16):
    pass


class View_float32(_ecvl.View_float32):
    pass


def CopyImage(src, dst, new_type=None):
    if new_type is None:
        return _ecvl.CopyImage(src, dst)
    return _ecvl.CopyImage(src, dst, new_type)


def RearrangeChannels(src, dst, channels, new_type=None):
    if new_type is None:
        return _ecvl.RearrangeChannels(src, dst, channels)
    return _ecvl.RearrangeChannels(src, dst, channels, new_type)


# == arithmetic ==

def And(src1, src2, dst):
    return _ecvl.And(src1, src2, dst)


def Neg(img):
    return _ecvl.Neg(img)


def Or(src1, src2, dst):
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
