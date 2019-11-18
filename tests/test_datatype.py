import pyecvl._core.ecvl as ecvl


def test_size():
    assert ecvl.DataTypeSize(ecvl.DataType.int8) == 1
    assert ecvl.DataTypeSize(ecvl.DataType.int16) == 2
    assert ecvl.DataTypeSize(ecvl.DataType.int32) == 4
    assert ecvl.DataTypeSize(ecvl.DataType.int64) == 8
    assert ecvl.DataTypeSize(ecvl.DataType.float32) == 4
    assert ecvl.DataTypeSize(ecvl.DataType.float64) == 8
    assert ecvl.DataTypeSize(ecvl.DataType.uint8) == 1
    assert ecvl.DataTypeSize(ecvl.DataType.uint16) == 2


def test_size_no_args():
    assert ecvl.DataTypeSize() == 8
    assert ecvl.DataTypeSignedSize() == 6
