import pyecvl._core.ecvl as ecvl
import pyeddl._core.eddlT as eddlT


def test_ImageToTensor():
    # 3D
    dims = [20, 30, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    t = ecvl.ImageToTensor(img)
    eddlT.max(t)
    assert t.shape == [dims[2], dims[1], dims[0]]
    # 4D
    dims = [20, 30, 5, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyzc", ecvl.ColorType.BGR)
    t = ecvl.ImageToTensor(img)
    assert t.shape == [dims[2], dims[3], dims[1], dims[0]]
    eddlT.max(t)


def test_TensorToImage():
    # 3D
    shape = [3, 30, 20]
    t = eddlT.create(shape)
    img = ecvl.TensorToImage(t)
    assert img.dims_ == [shape[2], shape[1], shape[0]]
    img = ecvl.TensorToImage(t, ecvl.ColorType.none)
    assert img.dims_ == [shape[2], shape[1], shape[0]]
    # 4D
    shape = [5, 3, 30, 20]
    t = eddlT.create(shape)
    img = ecvl.TensorToImage(t)
    assert img.dims_ == [shape[3], shape[2], shape[0], shape[1]]
    img = ecvl.TensorToImage(t, ecvl.ColorType.none)
    assert img.dims_ == [shape[3], shape[2], shape[0], shape[1]]
