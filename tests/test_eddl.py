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

import io
import pytest
import numpy as np

import pyecvl._core.ecvl as ecvl_core
import pyecvl.ecvl as ecvl_py
tensor = pytest.importorskip("pyeddl.tensor")


IMAGES = [f"foo_{i}.png" for i in range(3)]
GROUND_TRUTHS = [f"foo_{i}_gt.png" for i in range(3)]

SEG_DATASET = f"""\
name: Foo
description: FooDesc
images:
- location: {IMAGES[0]}
  label: {GROUND_TRUTHS[0]}
- location: {IMAGES[1]}
  label: {GROUND_TRUTHS[1]}
- location: {IMAGES[2]}
  label: {GROUND_TRUTHS[2]}
split:
  training:
  - 0
  - 1
  test:
  - 2
"""

CLS_DATASET = f"""\
name: Foo
description: FooDesc
classes:
- '0'
- '1'
images:
- location: {IMAGES[0]}
  label: 0
- location: {IMAGES[1]}
  label: 1
- location: {IMAGES[2]}
  label: 1
split:
  training:
  - 0
  - 1
  test:
  - 2
"""


def _build_dataset(dir_path, type_="seg"):
    fn = str(dir_path / "foo.yml")
    with io.open(fn, "wt") as f:
        f.write(SEG_DATASET if type_ == "seg" else CLS_DATASET)
    for name in IMAGES:
        a = np.random.randint(0, 255, [20, 40, 3], dtype=np.uint8)
        img = ecvl_py.Image.fromarray(a, "xyc", ecvl_py.ColorType.RGB)
        ecvl_py.ImWrite(str(dir_path / name), img)
    if type_ == "seg":
        for name in GROUND_TRUTHS:
            a = np.random.randint(0, 255, [20, 40, 1], dtype=np.uint8)
            img = ecvl_py.Image.fromarray(a, "xyc", ecvl_py.ColorType.GRAY)
            ecvl_py.ImWrite(str(dir_path / name), img)
    return fn


def _img_fromarray(ecvl, array, channels, colortype, spacings=None):
    if spacings is None:
        spacings = []
    if ecvl is ecvl_core:
        return ecvl.Image(array, channels, colortype, spacings)
    return ecvl.Image.fromarray(array, channels, colortype, spacings)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_DatasetAugmentations(ecvl):
    img = ecvl.Image([5, 4, 3], ecvl.DataType.uint8, "xyc", ecvl.ColorType.RGB)
    training_augs = ecvl.SequentialAugmentationContainer([
        ecvl.AugRotate([-5, 5]),
        ecvl.AugMirror(.5),
    ])
    validation_augs = ecvl.SequentialAugmentationContainer([
        ecvl.AugResizeDim([30, 30]),
        ecvl.AugToFloat32(255),
    ])
    ds_augs = ecvl.DatasetAugmentations([training_augs, validation_augs])
    assert not ds_augs.IsEmpty()
    ds_augs.Apply(ecvl.SplitType.training, img)
    ds_augs.Apply(ecvl.SplitType.validation, img)
    assert ecvl.DatasetAugmentations([]).IsEmpty()


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_ProducersConsumerQueue(ecvl):
    s = ecvl.Sample()
    s.location_, s.size_ = ["foo.png"], [400, 300]
    img_tensor = tensor.Tensor([5, 4, 3])
    gt_tensor = tensor.Tensor([5, 4, 3])
    q = ecvl.ProducersConsumerQueue(5)
    assert not q.IsFull()
    assert q.IsEmpty()
    assert q.Length() == 0
    q.Push(s, img_tensor, gt_tensor)
    assert not q.IsFull()
    assert not q.IsEmpty()
    assert q.Length() == 1
    s_, img_tensor_, gt_tensor_ = q.Pop()
    assert not q.IsFull()
    assert q.IsEmpty()
    assert q.Length() == 0
    assert s_.location_ == s.location_
    assert s_.size_ == s.size_
    assert img_tensor_ is img_tensor
    assert gt_tensor_ is gt_tensor
    q.SetSize(1, -1)
    q.Push(s, img_tensor, gt_tensor)
    assert q.IsFull()
    q.SetSize(8)
    assert not q.IsFull()
    q.Clear()
    assert q.IsEmpty()


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_ThreadCounters(ecvl):
    tc = ecvl.ThreadCounters(10, 30)
    assert tc.counter_ == tc.min_ == 10
    assert tc.max_ == 30
    tc = ecvl.ThreadCounters(20, 10, 30)
    assert tc.counter_ == 20
    assert tc.min_ == 10
    assert tc.max_ == 30
    tc.counter_ = 25
    tc.Reset()
    assert tc.counter_ == 10


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_ImageToTensor(ecvl):
    dims = [20, 30, 3]
    img = ecvl.Image(dims, ecvl.DataType.uint8, "xyc", ecvl.ColorType.BGR)
    t = ecvl.ImageToTensor(img)
    t.max()
    assert t.shape == [dims[2], dims[1], dims[0]]


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_ImageToTensor_offset(ecvl):
    a = np.arange(24).reshape((3, 4, 2)).astype(np.uint8)
    b = np.arange(24, 48).reshape((3, 4, 2)).astype(np.uint8)
    a_img = _img_fromarray(ecvl, a, "xyc", ecvl.ColorType.BGR)
    b_img = _img_fromarray(ecvl, b, "xyc", ecvl.ColorType.BGR)
    t = ecvl.ImageToTensor(a_img)
    u = ecvl.ImageToTensor(b_img)
    assert t.shape == [2, 4, 3]
    t_arr = t.getdata()
    assert u.shape == [2, 4, 3]
    u_arr = u.getdata()
    v = tensor.Tensor([4, 4, 3])
    ecvl.ImageToTensor(a_img, v, 0)
    ecvl.ImageToTensor(b_img, v, 1)
    v_arr = v.getdata()
    assert np.array_equal(v_arr[:2], t_arr)
    assert np.array_equal(v_arr[2:], u_arr)
    if ecvl is ecvl_py:
        with pytest.raises(ValueError):
            ecvl.ImageToTensor(a_img, None, 0)
        with pytest.raises(ValueError):
            ecvl.ImageToTensor(a_img, v, None)


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_TensorToImage(ecvl):
    # 3D
    shape = [3, 30, 20]
    t = tensor.Tensor(shape)
    img = ecvl.TensorToImage(t)
    assert img.dims_ == [shape[2], shape[1], shape[0]]
    # 4D
    shape = [5, 3, 30, 20]
    t = tensor.Tensor(shape)
    img = ecvl.TensorToImage(t)
    assert img.dims_ == [shape[3], shape[2], shape[0] * shape[1]]


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_TensorToView(ecvl):
    # 3D
    shape = [3, 30, 20]
    t = tensor.Tensor(shape)
    view = ecvl.TensorToView(t)
    assert view.dims_ == [shape[2], shape[1], shape[0]]
    # 4D
    shape = [5, 3, 30, 20]
    t = tensor.Tensor(shape)
    view = ecvl.TensorToView(t)
    assert view.dims_ == [shape[3], shape[2], shape[0] * shape[1]]


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_DLDataset_seg(ecvl, tmp_path):
    augs = ecvl.DatasetAugmentations([ecvl.AugFlip(0.5)])
    fn = _build_dataset(tmp_path, "seg")
    batch_size = 1
    d = ecvl.DLDataset(fn, batch_size, augs)
    assert d.n_channels_ == 3
    assert d.n_channels_gt_ == 1
    d.ResetBatch()
    d.ResetBatch(0)
    d.ResetBatch(0, True)
    d.ResetAllBatches()
    d.ResetAllBatches(True)
    x = tensor.Tensor([batch_size, d.n_channels_, d.resize_dims_[0], d.resize_dims_[1]])
    d.LoadBatch(x)
    ecvl.DLDataset.SetSplitSeed(12345)
    d.ResetBatch()
    d.SetWorkers(1)
    d.Start()
    assert len(d.GetBatch()) == 3
    d.Stop()
    d.SetNumChannels(1)
    d.SetNumChannels(1, 1)
    assert d.GetQueueSize() < len(d.samples_)
    d.SetAugmentations(ecvl.DatasetAugmentations([ecvl.AugFlip(0.9)]))
    assert d.GetNumBatches() == d.GetNumBatches(ecvl.SplitType.training) == 2
    assert d.GetNumBatches(ecvl.SplitType.test) == 1


@pytest.mark.parametrize("ecvl", [ecvl_core, ecvl_py])
def test_DLDataset_cls(ecvl, tmp_path):
    augs = ecvl.DatasetAugmentations([ecvl.AugFlip(0.5)])
    fn = _build_dataset(tmp_path, "cls")
    batch_size = 2
    d = ecvl.DLDataset(fn, batch_size, augs)
    assert d.n_channels_ == 3
    x = tensor.Tensor([batch_size, d.n_channels_, d.resize_dims_[0], d.resize_dims_[1]])
    y = tensor.Tensor([batch_size, len(d.classes_)])
    d.LoadBatch(x, y)
    t = d.ToTensorPlane(d.samples_[0].label_)
    assert np.allclose(np.array(t), [1, 0])
    t = d.ToTensorPlane(d.samples_[1].label_)
    assert np.allclose(np.array(t), [0, 1])
