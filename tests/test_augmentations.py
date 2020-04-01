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

import pytest
import pyecvl._core.ecvl as ecvl


def test_AugmentationParam():
    ap = ecvl.AugmentationParam()
    min_, max_ = 0.1, 1.2
    ap = ecvl.AugmentationParam(min_, max_)
    assert ap.min_ == pytest.approx(min_)
    assert ap.max_ == pytest.approx(max_)
    ecvl.AugmentationParam.SetSeed(12345)
    ap.GenerateValue()
    assert min_ <= ap.value_ <= max_


def test_AugRotate():
    img = ecvl.Image([5, 4, 3], ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    a = ecvl.AugRotate([30, 50])
    a.Apply(img)
    a = ecvl.AugRotate([30, 50], [2, 3])
    a.Apply(img)
    a = ecvl.AugRotate([30, 50], [2, 3], 1.1)
    a.Apply(img)
    a = ecvl.AugRotate([30, 50], [2, 3], 1.1, ecvl.InterpolationType.nearest)
    a.Apply(img)


def test_AugResizeDim():
    img = ecvl.Image([5, 4, 3], ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    a = ecvl.AugResizeDim([4, 3])
    a.Apply(img)
    a = ecvl.AugResizeDim([4, 3], ecvl.InterpolationType.nearest)
    a.Apply(img)


def test_AugResizeScale():
    img = ecvl.Image([5, 4, 3], ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    a = ecvl.AugResizeScale([0.5, 0.5])
    a.Apply(img)
    a = ecvl.AugResizeScale([0.5, 0.5], ecvl.InterpolationType.nearest)
    a.Apply(img)


def test_AugFlip():
    img = ecvl.Image([5, 4, 3], ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    a = ecvl.AugFlip(0.5)
    a.Apply(img)


def test_AugMirror():
    img = ecvl.Image([5, 4, 3], ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    a = ecvl.AugMirror(0.5)
    a.Apply(img)


def test_AugGaussianBlur():
    img = ecvl.Image([5, 4, 3], ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    a = ecvl.AugGaussianBlur([0.2, 0.4])
    a.Apply(img)


def test_AugAdditiveLaplaceNoise():
    img = ecvl.Image([5, 4, 3], ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    a = ecvl.AugAdditiveLaplaceNoise([255 * 0.05, 255 * 0.09])
    a.Apply(img)


def test_AugAdditivePoissonNoise():
    img = ecvl.Image([5, 4, 3], ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    a = ecvl.AugAdditivePoissonNoise([2.0, 3.0])
    a.Apply(img)


def test_AugGammaContrast():
    img = ecvl.Image([5, 4, 3], ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    a = ecvl.AugGammaContrast([3, 4])
    a.Apply(img)


def test_AugCoarseDropout():
    img = ecvl.Image([5, 4, 3], ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    a = ecvl.AugCoarseDropout([0.5, 0.7], [0.1, 0.2], 0.4)
    a.Apply(img)
