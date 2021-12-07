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

import numpy as np
import pytest

import pyecvl._core.ecvl as ecvl_core
import pyecvl.ecvl as ecvl_py


def _empty_img(ecvl):
    if ecvl is ecvl_core:
        return ecvl.Image()
    return ecvl.Image.empty()


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_ResizeDim(ecvl):
    dims = [20, 40, 3]
    newdims = [10, 20]  # no color channel
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = _empty_img(ecvl)
    ecvl.ResizeDim(img, tmp, newdims)
    assert tmp.dims_[:2] == newdims
    ecvl.ResizeDim(img, tmp, newdims, ecvl.InterpolationType.nearest)
    assert tmp.dims_[:2] == newdims


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_ResizeScale(ecvl):
    dims = [20, 40, 3]
    scales = [0.5, 0.5]  # no color channel
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = _empty_img(ecvl)
    ecvl.ResizeScale(img, tmp, scales)
    assert tmp.dims_[:2] == [10, 20]
    ecvl.ResizeScale(img, tmp, scales, ecvl.InterpolationType.cubic)
    assert tmp.dims_[:2] == [10, 20]


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_Flip2D(ecvl):
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = _empty_img(ecvl)
    ecvl.Flip2D(img, tmp)
    assert tmp.dims_ == img.dims_


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_Mirror2D(ecvl):
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = _empty_img(ecvl)
    ecvl.Mirror2D(img, tmp)
    assert tmp.dims_ == img.dims_


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_Rotate2D(ecvl):
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = _empty_img(ecvl)
    angle, center, scale, interp = 9, [5, 5], 1.5, ecvl.InterpolationType.area
    ecvl.Rotate2D(img, tmp, angle)
    ecvl.Rotate2D(img, tmp, angle, center)
    ecvl.Rotate2D(img, tmp, angle, center, scale)
    ecvl.Rotate2D(img, tmp, angle, center, scale, interp)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_RotateFullImage2D(ecvl):
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = _empty_img(ecvl)
    angle, scale, interp = 9, 1.5, ecvl.InterpolationType.lanczos4
    ecvl.RotateFullImage2D(img, tmp, angle)
    ecvl.RotateFullImage2D(img, tmp, angle, scale)
    ecvl.RotateFullImage2D(img, tmp, angle, scale, interp)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_ChangeColorSpace(ecvl):
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = _empty_img(ecvl)
    new_color = ecvl.ColorType.GRAY
    ecvl.ChangeColorSpace(img, tmp, new_color)
    assert tmp.colortype_ == new_color
    assert tmp.dims_[-1] == 1


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_Threshold(ecvl):
    dims = [20, 40, 1]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.GRAY)
    thr = ecvl.OtsuThreshold(img)
    tmp = _empty_img(ecvl)
    ttype = ecvl.ThresholdingType.BINARY_INV
    ecvl.Threshold(img, tmp, thr, 255)
    ecvl.Threshold(img, tmp, thr, 255, ttype)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_MultiThreshold(ecvl):
    dims = [20, 40, 1]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.GRAY)
    thresholds = ecvl.OtsuMultiThreshold(img)
    tmp = _empty_img(ecvl)
    ecvl.MultiThreshold(img, tmp, thresholds)
    ecvl.MultiThreshold(img, tmp, thresholds, 1)
    ecvl.MultiThreshold(img, tmp, thresholds, 1, 254)
    thresholds = ecvl.OtsuMultiThreshold(img, 3)
    tmp = _empty_img(ecvl)
    ecvl.MultiThreshold(img, tmp, thresholds)
    ecvl.MultiThreshold(img, tmp, thresholds, 1)
    ecvl.MultiThreshold(img, tmp, thresholds, 1, 254)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_Filter2D(ecvl):
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = _empty_img(ecvl)
    # kernel must be float64, "xyc" and with one color channel
    kernel = ecvl.Image(
        [3, 3, 1], ecvl.DataType.float64, "xyc", ecvl.ColorType.GRAY
    )
    a = np.array(kernel, copy=False)
    a.fill(0.11)
    dtype = ecvl.DataType.uint16
    ecvl.Filter2D(img, tmp, kernel)
    ecvl.Filter2D(img, tmp, kernel, dtype)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_SeparableFilter2D(ecvl):
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = _empty_img(ecvl)
    kerX, kerY, dtype = [1, 2, 1], [1, 0, -1], ecvl.DataType.uint16
    ecvl.SeparableFilter2D(img, tmp, kerX, kerY)
    ecvl.SeparableFilter2D(img, tmp, kerX, kerY, dtype)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_GaussianBlur(ecvl):
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = _empty_img(ecvl)
    sigmaY = 0.2
    ecvl.GaussianBlur(img, tmp, 5, 5, 0.1)
    ecvl.GaussianBlur(img, tmp, 5, 5, 0.1, sigmaY)
    # alt overload in the ext module, called "GaussianBlur2" in the wrapper
    GaussianBlur2 = getattr(ecvl, "GaussianBlur2", ecvl.GaussianBlur)
    GaussianBlur2(img, tmp, 0.2)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_AdditiveLaplaceNoise(ecvl):
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = _empty_img(ecvl)
    stddev = 255 * 0.05
    ecvl.AdditiveLaplaceNoise(img, tmp, stddev)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_AdditivePoissonNoise(ecvl):
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = _empty_img(ecvl)
    lambda_ = 2.0
    ecvl.AdditivePoissonNoise(img, tmp, lambda_)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_GammaContrast(ecvl):
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = _empty_img(ecvl)
    gamma = 3
    ecvl.GammaContrast(img, tmp, gamma)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_CoarseDropout(ecvl):
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = _empty_img(ecvl)
    prob, drop_size, per_channel = 0.5, 0.1, True
    ecvl.CoarseDropout(img, tmp, prob, drop_size, per_channel)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_IntegralImage(ecvl):
    dims = [20, 40, 1]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.GRAY)
    tmp = _empty_img(ecvl)
    dst_type = ecvl.DataType.float64
    ecvl.IntegralImage(img, tmp)
    ecvl.IntegralImage(img, tmp, dst_type)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_NonMaximaSuppression(ecvl):
    dims = [20, 40, 1]
    img = ecvl.Image(dims, ecvl.DataType.int32, "xyc", ecvl.ColorType.GRAY)
    tmp = _empty_img(ecvl)
    ecvl.NonMaximaSuppression(img, tmp)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_GetMaxN(ecvl):
    a = np.asfortranarray(np.zeros(12, dtype=np.int32).reshape(3, 4, 1))
    a[0, 1] = 3
    a[1, 2] = 4
    if ecvl is ecvl_core:
        img = ecvl.Image(a, "xyc", ecvl.ColorType.GRAY)
    else:
        img = ecvl.Image.fromarray(a, "xyc", ecvl.ColorType.GRAY)
    assert sorted(ecvl.GetMaxN(img, 2)) == [[0, 1], [1, 2]]


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_ConnectedComponentsLabeling(ecvl):
    dims = [20, 40, 1]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.GRAY)
    tmp = _empty_img(ecvl)
    ecvl.ConnectedComponentsLabeling(img, tmp)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_FindContours(ecvl):
    dims = [20, 40, 1]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.GRAY)
    ecvl.FindContours(img)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_HConcat(ecvl):
    img1 = ecvl.Image(
        [20, 40, 3], ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR
    )
    img2 = ecvl.Image(
        [40, 40, 3], ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR
    )
    tmp = _empty_img(ecvl)
    ecvl.HConcat([img1, img2], tmp)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_VConcat(ecvl):
    img1 = ecvl.Image(
        [20, 40, 3], ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR
    )
    img2 = ecvl.Image(
        [20, 20, 3], ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR
    )
    tmp = _empty_img(ecvl)
    ecvl.VConcat([img1, img2], tmp)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_Stack(ecvl):
    img1 = ecvl.Image(
        [20, 40, 3], ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR
    )
    img2 = ecvl.Image(
        [20, 40, 3], ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR
    )
    tmp = _empty_img(ecvl)
    ecvl.Stack([img1, img2], tmp)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_Morphology(ecvl):
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    kernel = ecvl.Image(
        [5, 5, 1], ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR
    )
    tmp = _empty_img(ecvl)
    ecvl.Morphology(img, tmp, ecvl.MorphType.MORPH_BLACKHAT, kernel)
    ecvl.Morphology(img, tmp, ecvl.MorphType.MORPH_BLACKHAT, kernel, [3, 3])
    ecvl.Morphology(
        img, tmp, ecvl.MorphType.MORPH_BLACKHAT, kernel, [3, 3], 2
    )
    ecvl.Morphology(
        img, tmp, ecvl.MorphType.MORPH_BLACKHAT, kernel, [3, 3], 2,
        ecvl.BorderType.BORDER_REFLECT
    )
    ecvl.Morphology(
        img, tmp, ecvl.MorphType.MORPH_BLACKHAT, kernel, [3, 3], 2,
        ecvl.BorderType.BORDER_REFLECT, 1
    )


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_Inpaint(ecvl):
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    mask = ecvl.Image(
        [20, 40, 1], ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR
    )
    tmp = _empty_img(ecvl)
    ecvl.Inpaint(img, tmp, mask, 5.0)
    ecvl.Inpaint(img, tmp, mask, 5.0, ecvl.InpaintType.INPAINT_NS)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_MeanStdDev(ecvl):
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    mean, stddev = ecvl.MeanStdDev(img)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_Transpose(ecvl):
    img = ecvl.Image(
        [20, 40, 3], ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR
    )
    tmp = _empty_img(ecvl)
    ecvl.Transpose(img, tmp)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_GridDistortion(ecvl):
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = _empty_img(ecvl)
    ecvl.GridDistortion(img, tmp)
    ecvl.GridDistortion(img, tmp, 6)
    ecvl.GridDistortion(img, tmp, 6, [-0.5, 0.5])
    ecvl.GridDistortion(
        img, tmp, 6, [-0.5, 0.5], ecvl.InterpolationType.nearest
    )
    ecvl.GridDistortion(
        img, tmp, 6, [-0.5, 0.5], ecvl.InterpolationType.nearest,
        ecvl.BorderType.BORDER_CONSTANT
    )
    ecvl.GridDistortion(
        img, tmp, 6, [-0.5, 0.5], ecvl.InterpolationType.nearest,
        ecvl.BorderType.BORDER_CONSTANT, 1
    )
    ecvl.GridDistortion(
        img, tmp, 6, [-0.5, 0.5], ecvl.InterpolationType.nearest,
        ecvl.BorderType.BORDER_CONSTANT, 1, 12345
    )


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_ElasticTransform(ecvl):
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = _empty_img(ecvl)
    ecvl.ElasticTransform(img, tmp)
    ecvl.ElasticTransform(img, tmp, 35)
    ecvl.ElasticTransform(img, tmp, 35, 5)
    ecvl.ElasticTransform(img, tmp, 35, 5, ecvl.InterpolationType.nearest)
    ecvl.ElasticTransform(
        img, tmp, 35, 5, ecvl.InterpolationType.nearest,
        ecvl.BorderType.BORDER_CONSTANT
    )
    ecvl.ElasticTransform(
        img, tmp, 35, 5, ecvl.InterpolationType.nearest,
        ecvl.BorderType.BORDER_CONSTANT, 1
    )
    ecvl.ElasticTransform(
        img, tmp, 35, 5, ecvl.InterpolationType.nearest,
        ecvl.BorderType.BORDER_CONSTANT, 1, 12345
    )


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_OpticalDistortion(ecvl):
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = _empty_img(ecvl)
    ecvl.OpticalDistortion(img, tmp)
    ecvl.OpticalDistortion(img, tmp)
    ecvl.OpticalDistortion(img, tmp, [-0.5, 0.5])
    ecvl.OpticalDistortion(img, tmp, [-0.5, 0.5], [-0.2, 0.2])
    ecvl.OpticalDistortion(
        img, tmp, [-0.5, 0.5], [-0.2, 0.2], ecvl.InterpolationType.nearest
    )
    ecvl.OpticalDistortion(
        img, tmp, [-0.5, 0.5], [-0.2, 0.2], ecvl.InterpolationType.nearest,
        ecvl.BorderType.BORDER_CONSTANT
    )
    ecvl.OpticalDistortion(
        img, tmp, [-0.5, 0.5], [-0.2, 0.2], ecvl.InterpolationType.nearest,
        ecvl.BorderType.BORDER_CONSTANT, 12345
    )


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_Salt(ecvl):
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = _empty_img(ecvl)
    ecvl.Salt(img, tmp, 0.4)
    ecvl.Salt(img, tmp, 0.4, True)
    ecvl.Salt(img, tmp, 0.4, True, 12345)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_Pepper(ecvl):
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = _empty_img(ecvl)
    ecvl.Pepper(img, tmp, 0.4)
    ecvl.Pepper(img, tmp, 0.4, True)
    ecvl.Pepper(img, tmp, 0.4, True, 12345)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_SaltAndPepper(ecvl):
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = _empty_img(ecvl)
    ecvl.SaltAndPepper(img, tmp, 0.4)
    ecvl.SaltAndPepper(img, tmp, 0.4, True)
    ecvl.SaltAndPepper(img, tmp, 0.4, True, 12345)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_SliceTimingCorrection(ecvl):
    dims = [20, 40, 10, 30]
    spacings = [1, 2, 3, 4]
    img = ecvl.Image(
        dims, ecvl.DataType.float32, "xyzt", ecvl.ColorType.none, spacings
    )
    tmp = _empty_img(ecvl)
    ecvl.SliceTimingCorrection(img, tmp)
    ecvl.SliceTimingCorrection(img, tmp, True)
    ecvl.SliceTimingCorrection(img, tmp, True, True)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_DrawEllipse(ecvl):
    dims = [20, 20, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    ecvl.DrawEllipse(img, [10, 10], [7, 5], 15, [100])
    ecvl.DrawEllipse(img, [10, 10], [7, 5], 15, [50, 50, 50])
    ecvl.DrawEllipse(img, [10, 10], [7, 5], 15, [50, 50, 50], 2)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_Moments(ecvl):
    dims = [20, 20, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.GRAY)
    moments = _empty_img(ecvl)
    ecvl.Moments(img, moments)
    assert moments.dims_ == [4, 4]
    assert moments.elemtype_ == ecvl.DataType.float64
    ecvl.Moments(img, moments, 2)
    assert moments.dims_ == [3, 3]
    assert moments.elemtype_ == ecvl.DataType.float64
    datatype = ecvl.DataType.float32
    ecvl.Moments(img, moments, 2, datatype)
    assert moments.dims_ == [3, 3]
    assert moments.elemtype_ == datatype


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_CentralMoments(ecvl):
    dims = [20, 20, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.GRAY)
    moments = _empty_img(ecvl)
    ecvl.CentralMoments(img, moments, [10., 10.])
    assert moments.dims_ == [4, 4]
    assert moments.elemtype_ == ecvl.DataType.float64
    ecvl.CentralMoments(img, moments, [10., 10.], 2)
    assert moments.dims_ == [3, 3]
    assert moments.elemtype_ == ecvl.DataType.float64
    datatype = ecvl.DataType.float32
    ecvl.CentralMoments(img, moments, [10., 10.], 2, datatype)
    assert moments.dims_ == [3, 3]
    assert moments.elemtype_ == datatype


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_DropColorChannel(ecvl):
    dims = [20, 20, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.GRAY)
    ecvl.DropColorChannel(img)
    assert img.dims_ == [20, 20]
    assert img.channels_ == "xy"
    assert img.colortype_ == ecvl.ColorType.none


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_Normalize(ecvl):
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = _empty_img(ecvl)
    ecvl.Normalize(img, tmp, 20, 5.5)
    ecvl.Normalize(img, tmp, [20], [5.5])


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_Normalize_separate(ecvl):
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = _empty_img(ecvl)
    ecvl.Normalize(img, tmp, [20, 19, 21], [5, 5.5, 6])


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_CenterCrop(ecvl):
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = _empty_img(ecvl)
    ecvl.CenterCrop(img, tmp, [10, 20])


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_ScaleTo(ecvl):
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = _empty_img(ecvl)
    ecvl.ScaleTo(img, tmp, 1, 254)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_Pad(ecvl):
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = _empty_img(ecvl)
    for padding in [3], [2, 3], [1, 2, 3, 4]:
        ecvl.Pad(img, tmp, padding)
    ecvl.Pad(img, tmp, [3], ecvl.BorderType.BORDER_REFLECT_101)
    ecvl.Pad(img, tmp, [3], ecvl.BorderType.BORDER_CONSTANT, 255)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_RandomCrop(ecvl):
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = _empty_img(ecvl)
    ecvl.RandomCrop(img, tmp, [10, 20])
    with pytest.raises(RuntimeError):
        ecvl.RandomCrop(img, tmp, [22, 42])
    ecvl.RandomCrop(img, tmp, [22, 42], True)
    ecvl.RandomCrop(img, tmp, [22, 42], True, ecvl.BorderType.BORDER_REFLECT_101)
    ecvl.RandomCrop(img, tmp, [22, 42], True, ecvl.BorderType.BORDER_CONSTANT, 1)
    ecvl.RandomCrop(img, tmp, [22, 42], True, ecvl.BorderType.BORDER_CONSTANT, 1, 12345)
