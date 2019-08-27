#!/bin/bash

set -euo pipefail

this="${BASH_SOURCE:-$0}"
this_dir=$(cd -P -- "$(dirname -- "${this}")" && pwd -P)

pushd "${this_dir}"
rm -rf include && mkdir include
docker run --rm ecvl bash -c "tar -c -C /usr/include opencv2" | tar -x -C include
popd

pyecvl_mount=/pyecvl

docker run --rm -v "${this_dir}":"${pyecvl_mount}" \
  -e BINDER_EXE='/binder/build/llvm-4.0.0/build_4.0.0*/bin/binder' \
  -e ADD_INCLUDE="-I${pyecvl_mount}/third_party/ecvl/modules/core/include -I${pyecvl_mount}/include -I${pyecvl_mount}/src" \
  -w "${pyecvl_mount}"/codegen crs4/binder:f3f6919 ./gen_bindings.sh
cp codegen/bindings/_core.cpp src/
