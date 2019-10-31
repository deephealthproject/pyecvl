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


def test_Rotate2D():
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = ecvl.Image()
    angle, center, scale, interp = 9, [5, 5], 1.5, ecvl.InterpolationType.cubic
    ecvl.Rotate2D(img, tmp, angle)
    ecvl.Rotate2D(img, tmp, angle, center)
    ecvl.Rotate2D(img, tmp, angle, center, scale)
    ecvl.Rotate2D(img, tmp, angle, center, scale, interp)


def test_SeparableFilter2D():
    dims = [20, 40, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    tmp = ecvl.Image()
    kerX, kerY, dtype = [1, 2, 1], [1, 0, -1], ecvl.DataType.uint16
    ecvl.SeparableFilter2D(img, tmp, kerX, kerY)
    ecvl.SeparableFilter2D(img, tmp, kerX, kerY, dtype)
