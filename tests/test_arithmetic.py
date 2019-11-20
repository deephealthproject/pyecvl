import numpy as np
import pyecvl._core.ecvl as ecvl


def test_Neg():
    dims = [2, 3, 1]
    z = ecvl.Image(dims, ecvl.DataType.int8, "xyc", ecvl.ColorType.GRAY)
    d = np.array(z, copy=False)
    d.fill(10)
    ecvl.Neg(z)
    assert (d == -10).all()


def test_And():
    dims = [2, 3, 1]
    x = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.GRAY)
    y = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.GRAY)
    a = np.array(x, copy=False)
    b = np.array(y, copy=False)
    tmp = ecvl.Image()
    a.fill(5)
    b.fill(14)
    ecvl.And(x, y, tmp)
    c = np.array(tmp, copy=False)
    assert (c == (5 & 14)).all()


def test_Or():
    dims = [2, 3, 1]
    x = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.GRAY)
    y = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.GRAY)
    a = np.array(x, copy=False)
    b = np.array(y, copy=False)
    tmp = ecvl.Image()
    a.fill(5)
    b.fill(14)
    ecvl.Or(x, y, tmp)
    c = np.array(tmp, copy=False)
    assert (c == (5 | 14)).all()
