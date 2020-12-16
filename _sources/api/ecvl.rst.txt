.. _ecvl:

:mod:`pyecvl.ecvl` --- ecvl API
===============================


Data types
----------

.. autoclass:: pyecvl.ecvl.DataType
   :members:
   :undoc-members:

.. autofunction:: pyecvl.ecvl.DataTypeSize

.. autofunction:: pyecvl.ecvl.DataTypeSignedSize


Color types
-----------

.. autoclass:: pyecvl.ecvl.ColorType
   :members:
   :undoc-members:


Device types
------------

.. autoclass:: pyecvl.ecvl.Device
   :members:
   :undoc-members:


Image
-----

.. autoclass:: pyecvl.ecvl.Image
   :members:
   :undoc-members:

.. autofunction:: pyecvl.ecvl.CopyImage

.. autofunction:: pyecvl.ecvl.ShallowCopyImage

.. autofunction:: pyecvl.ecvl.RearrangeChannels


Arithmetic operations
---------------------

.. autofunction:: pyecvl.ecvl.Neg

.. autofunction:: pyecvl.ecvl.Add

.. autofunction:: pyecvl.ecvl.Sub

.. autofunction:: pyecvl.ecvl.Mul

.. autofunction:: pyecvl.ecvl.Div


Image processing
----------------

.. autoclass:: pyecvl.ecvl.ThresholdingType
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.InterpolationType
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.MorphType
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.InpaintType
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.BorderType
   :members:
   :undoc-members:

.. autofunction:: pyecvl.ecvl.ResizeDim

.. autofunction:: pyecvl.ecvl.ResizeScale

.. autofunction:: pyecvl.ecvl.Flip2D

.. autofunction:: pyecvl.ecvl.Mirror2D

.. autofunction:: pyecvl.ecvl.Rotate2D

.. autofunction:: pyecvl.ecvl.RotateFullImage2D

.. autofunction:: pyecvl.ecvl.ChangeColorSpace

.. autofunction:: pyecvl.ecvl.Threshold

.. autofunction:: pyecvl.ecvl.MultiThreshold

.. autofunction:: pyecvl.ecvl.OtsuThreshold

.. autofunction:: pyecvl.ecvl.OtsuMultiThreshold

.. autofunction:: pyecvl.ecvl.Filter2D

.. autofunction:: pyecvl.ecvl.SeparableFilter2D

.. autofunction:: pyecvl.ecvl.GaussianBlur

.. autofunction:: pyecvl.ecvl.GaussianBlur2

.. autofunction:: pyecvl.ecvl.AdditiveLaplaceNoise

.. autofunction:: pyecvl.ecvl.AdditivePoissonNoise

.. autofunction:: pyecvl.ecvl.GammaContrast

.. autofunction:: pyecvl.ecvl.CoarseDropout

.. autofunction:: pyecvl.ecvl.IntegralImage

.. autofunction:: pyecvl.ecvl.NonMaximaSuppression

.. autofunction:: pyecvl.ecvl.GetMaxN

.. autofunction:: pyecvl.ecvl.ConnectedComponentsLabeling

.. autofunction:: pyecvl.ecvl.FindContours

.. autofunction:: pyecvl.ecvl.Stack

.. autofunction:: pyecvl.ecvl.HConcat

.. autofunction:: pyecvl.ecvl.VConcat

.. autofunction:: pyecvl.ecvl.Morphology

.. autofunction:: pyecvl.ecvl.Inpaint

.. autofunction:: pyecvl.ecvl.MeanStdDev

.. autofunction:: pyecvl.ecvl.Transpose

.. autofunction:: pyecvl.ecvl.GridDistortion

.. autofunction:: pyecvl.ecvl.ElasticTransform

.. autofunction:: pyecvl.ecvl.OpticalDistortion

.. autofunction:: pyecvl.ecvl.Salt

.. autofunction:: pyecvl.ecvl.Pepper

.. autofunction:: pyecvl.ecvl.SaltAndPepper

.. autofunction:: pyecvl.ecvl.SliceTimingCorrection

.. autofunction:: pyecvl.ecvl.Moments

.. autofunction:: pyecvl.ecvl.CentralMoments

.. autofunction:: pyecvl.ecvl.DrawEllipse

.. autofunction:: pyecvl.ecvl.DropColorChannel

.. autofunction:: pyecvl.ecvl.Normalize


DeepHealth dataset parser
-------------------------

.. autoclass:: pyecvl.ecvl.SplitType
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.Sample
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.Split
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.Dataset
   :members:
   :undoc-members:


Augmentations
-------------

.. autoclass:: pyecvl.ecvl.AugmentationParam
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.AugmentationFactory
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.SequentialAugmentationContainer
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.OneOfAugmentationContainer
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.AugRotate
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.AugResizeDim
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.AugResizeScale
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.AugFlip
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.AugMirror
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.AugGaussianBlur
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.AugAdditiveLaplaceNoise
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.AugAdditivePoissonNoise
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.AugGammaContrast
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.AugCoarseDropout
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.AugTranspose
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.AugBrightness
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.AugGridDistortion
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.AugElasticTransform
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.AugOpticalDistortion
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.AugSalt
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.AugPepper
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.AugSaltAndPepper
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.AugNormalize
   :members:
   :undoc-members:


Image I/O
---------

.. autoclass:: pyecvl.ecvl.ImReadMode
   :members:
   :undoc-members:

.. autofunction:: pyecvl.ecvl.ImRead

.. autofunction:: pyecvl.ecvl.ImWrite

.. autofunction:: pyecvl.ecvl.OpenSlideGetLevels

.. autofunction:: pyecvl.ecvl.OpenSlideRead

.. autofunction:: pyecvl.ecvl.NiftiRead

.. autofunction:: pyecvl.ecvl.NiftiWrite

.. autofunction:: pyecvl.ecvl.DicomRead

.. autofunction:: pyecvl.ecvl.DicomWrite


EDDL support
------------

.. autoclass:: pyecvl.ecvl.DatasetAugmentations
   :members:
   :undoc-members:

.. autoclass:: pyecvl.ecvl.DLDataset
   :members:
   :undoc-members:

.. autofunction:: pyecvl.ecvl.ImageToTensor

.. autofunction:: pyecvl.ecvl.TensorToImage
