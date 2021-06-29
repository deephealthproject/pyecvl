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

echo "*** Running augmentations.py ***"
python3 augmentations.py "${root}"/test.jpg

echo "*** Running dataset.py ***"
python3 dataset.py "${root}"/mnist/mnist.yml

echo "*** Running dataset_generator.py ***"
python3 dataset_generator.py "${root}"/fake_classification_dataset "${root}"/fake_segmentation_dataset

echo "*** Running ecvl_eddl.py ***"
python3 ecvl_eddl.py "${root}"/test.jpg "${root}"/mnist/mnist.yml

echo "*** Running img_format.py ***"
python3 img_format.py "${root}"/nifti/LR_nifti.nii "${root}"/dicom/ISIC_0000008.dcm

echo "*** Running imgproc.py ***"
python3 imgproc.py "${root}"/test.jpg "${root}"/lena.png

echo "*** Running moments.py ***"
python3 moments.py "${root}"/example_ISIC_01.jpg

echo "*** Running openslide.py ***"
python3 openslide.py "${root}/hamamatsu/test3-DAPI 2 (387).ndpi"

echo "*** Running pipeline.py ***"
python3 pipeline.py "${root}"/mnist/mnist_reduced.yml

echo "*** Running read_write.py ***"
python3 read_write.py "${root}"/test.jpg test_mod.jpg

popd
