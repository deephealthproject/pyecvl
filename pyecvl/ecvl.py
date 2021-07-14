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

from . import _core
_ecvl = _core.ecvl

ECVL_EDDL = _ecvl.ECVL_EDDL
ECVL_WITH_OPENSLIDE = _ecvl.ECVL_WITH_OPENSLIDE
ECVL_WITH_DICOM = _ecvl.ECVL_WITH_DICOM

from .arithmetic import *  # noqa: E402,F401,F403
from .dataset_generator import *  # noqa: E402,F401,F403
from .dataset_parser import *  # noqa: E402,F401,F403
from .datatype import *  # noqa: E402,F401,F403
from .image import *  # noqa: E402,F401,F403
from .imgproc import *  # noqa: E402,F401,F403
from .support_imgcodecs import *  # noqa: E402,F401,F403
from .support_nifti import *  # noqa: E402,F401,F403
if ECVL_EDDL:
    from .augmentations import *  # noqa: E402,F401,F403
    from .support_eddl import *  # noqa: E402,F401,F403
if ECVL_WITH_OPENSLIDE:
    from .support_openslide import *  # noqa: E402,F401,F403
if ECVL_WITH_DICOM:
    from .support_dcmtk import *  # noqa: E402,F401,F403
