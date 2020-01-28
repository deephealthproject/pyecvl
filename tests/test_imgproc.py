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

import numpy as np
import pyecvl._core.ecvl as ecvl


def test_ResizeDim():
    dims = [20, 40, 3]
    newdims = [10, 20]  # no color channel
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = ecvl.Image()
    ecvl.ResizeDim(img, tmp, newdims)
    assert tmp.dims_[:2] == newdims
    ecvl.ResizeDim(img, tmp, newdims, ecvl.InterpolationType.nearest)
    assert tmp.dims_[:2] == newdims


def test_ResizeScale():
    dims = [20, 40, 3]
    scales = [0.5, 0.5]  # no color channel
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = ecvl.Image()
    ecvl.ResizeScale(img, tmp, scales)
    assert tmp.dims_[:2] == [10, 20]
    ecvl.ResizeScale(img, tmp, scales, ecvl.InterpolationType.cubic)
    assert tmp.dims_[:2] == [10, 20]


def test_Flip2D():
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = ecvl.Image()
    ecvl.Flip2D(img, tmp)
    assert tmp.dims_ == img.dims_


def test_Mirror2D():
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = ecvl.Image()
    ecvl.Mirror2D(img, tmp)
    assert tmp.dims_ == img.dims_


def test_Rotate2D():
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = ecvl.Image()
    angle, center, scale, interp = 9, [5, 5], 1.5, ecvl.InterpolationType.area
    ecvl.Rotate2D(img, tmp, angle)
    ecvl.Rotate2D(img, tmp, angle, center)
    ecvl.Rotate2D(img, tmp, angle, center, scale)
    ecvl.Rotate2D(img, tmp, angle, center, scale, interp)


def test_RotateFullImage2D():
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = ecvl.Image()
    angle, scale, interp = 9, 1.5, ecvl.InterpolationType.lanczos4
    ecvl.RotateFullImage2D(img, tmp, angle)
    ecvl.RotateFullImage2D(img, tmp, angle, scale)
    ecvl.RotateFullImage2D(img, tmp, angle, scale, interp)


def test_ChangeColorSpace():
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = ecvl.Image()
    new_color = ecvl.ColorType.GRAY
    ecvl.ChangeColorSpace(img, tmp, new_color)
    assert tmp.colortype_ == new_color
    assert tmp.dims_[-1] == 1


def test_Threshold():
    dims = [20, 40, 1]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.GRAY)
    thr = ecvl.OtsuThreshold(img)
    tmp = ecvl.Image()
    ttype = ecvl.ThresholdingType.BINARY_INV
    ecvl.Threshold(img, tmp, thr, 255)
    ecvl.Threshold(img, tmp, thr, 255, ttype)


def test_Filter2D():
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = ecvl.Image()
    # kernel must be float64, "xyc" and with one color channel
    kernel = ecvl.Image(
        [3, 3, 1], ecvl.DataType.float64, "xyc", ecvl.ColorType.GRAY
    )
    a = np.array(kernel, copy=False)
    a.fill(0.11)
    dtype = ecvl.DataType.uint16
    ecvl.Filter2D(img, tmp, kernel)
    ecvl.Filter2D(img, tmp, kernel, dtype)


def test_SeparableFilter2D():
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = ecvl.Image()
    kerX, kerY, dtype = [1, 2, 1], [1, 0, -1], ecvl.DataType.uint16
    ecvl.SeparableFilter2D(img, tmp, kerX, kerY)
    ecvl.SeparableFilter2D(img, tmp, kerX, kerY, dtype)


def test_GaussianBlur():
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = ecvl.Image()
    sigmaY = 0.2
    ecvl.GaussianBlur(img, tmp, 5, 5, 0.1)
    ecvl.GaussianBlur(img, tmp, 5, 5, 0.1, sigmaY)


def test_AdditiveLaplaceNoise():
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = ecvl.Image()
    stddev = 255 * 0.05
    ecvl.AdditiveLaplaceNoise(img, tmp, stddev)


def test_AdditivePoissonNoise():
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = ecvl.Image()
    lambda_ = 2.0
    ecvl.AdditivePoissonNoise(img, tmp, lambda_)


def test_GammaContrast():
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = ecvl.Image()
    gamma = 3
    ecvl.GammaContrast(img, tmp, gamma)


def test_CoarseDropout():
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = ecvl.Image()
    prob, drop_size, per_channel = 0.5, 0.1, True
    ecvl.CoarseDropout(img, tmp, prob, drop_size, per_channel)


def test_IntegralImage():
    dims = [20, 40, 1]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.GRAY)
    tmp = ecvl.Image()
    dst_type = ecvl.DataType.float64
    ecvl.IntegralImage(img, tmp)
    ecvl.IntegralImage(img, tmp, dst_type)


def test_NonMaximaSuppression():
    dims = [20, 40, 1]
    img = ecvl.Image(dims, ecvl.DataType.int32, "xyc", ecvl.ColorType.GRAY)
    tmp = ecvl.Image()
    ecvl.NonMaximaSuppression(img, tmp)


def test_GetMaxN():
    a = np.asfortranarray(np.zeros(12, dtype=np.int32).reshape(3, 4, 1))
    a[0, 1] = 3
    a[1, 2] = 4
    img = ecvl.Image(a, "xyc", ecvl.ColorType.GRAY)
    assert sorted(ecvl.GetMaxN(img, 2)) == [[0, 1], [1, 2]]


def test_ConnectedComponentsLabeling():
    dims = [20, 40, 1]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.GRAY)
    tmp = ecvl.Image()
    ecvl.ConnectedComponentsLabeling(img, tmp)


def test_FindContours():
    dims = [20, 40, 1]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.GRAY)
    ecvl.FindContours(img)
