#!/usr/bin/env bash

set -euo pipefail

this="${BASH_SOURCE-$0}"
this_dir=$(cd -P -- "$(dirname -- "${this}")" && pwd -P)

pushd "${this_dir}"
pushd third_party/ecvl
ecvl_rev=$(git rev-parse --short HEAD)
popd
pushd third_party/pyeddl
pyeddl_rev=$(git rev-parse --short HEAD)
pushd third_party/eddl
eddl_rev=$(git rev-parse --short HEAD)
[ "${eddl_rev}" = "c023a6e" -o "${eddl_rev}" = "01ef395" ] && git apply ../../eddl_0.3.patch
popd
docker build -t eddl:${eddl_rev} -f Dockerfile.eddl .
popd
docker build --build-arg eddl_rev=${eddl_rev} -t simleo/ecvl:${ecvl_rev}-${pyeddl_rev} -f Dockerfile.ecvl .
docker build -f Dockerfile.jenkins --build-arg ecvl_rev=${ecvl_rev} --build-arg pyeddl_rev=${pyeddl_rev} -t simleo/pyecvl-base:${ecvl_rev}-${pyeddl_rev} .
popd
