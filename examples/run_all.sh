#!/usr/bin/env bash

set -euo pipefail
[ -n "${DEBUG:-}" ] && set -x
this="${BASH_SOURCE-$0}"
this_dir=$(cd -P -- "$(dirname -- "${this}")" && pwd -P)

if [ $# -ne 1 ]; then
    echo "Usage: $0 ECVL_DATA_ROOT"
    exit 2
fi
root=$1

pushd "${this_dir}"
python3 augmentations.py "${root}"/test.jpg
python3 dataset.py "${root}"/mnist/mnist.yml
python3 dataset_generator.py "${root}"/fake_classification_dataset "${root}"/fake_segmentation_dataset
python3 ecvl_eddl.py "${root}"/test.jpg "${root}"/mnist/mnist.yml
python3 img_format.py "${root}"/nifti/LR_nifti.nii "${root}"/dicom/ISIC_0000008.dcm
python3 imgproc.py "${root}"/test.jpg "${root}"/lena.png
python3 moments.py "${root}"/example_ISIC_01.jpg
python3 openslide.py "${root}/hamamatsu/test3-DAPI 2 (387).ndpi"
python3 read_write.py "${root}"/test.jpg test_mod.jpg
popd
