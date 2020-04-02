#!/bin/bash

set -euo pipefail

this="${BASH_SOURCE:-$0}"
this_dir=$(cd -P -- "$(dirname -- "${this}")" && pwd -P)

pushd "${this_dir}"
rm -rf include && mkdir include
docker run --rm ecvl bash -c "tar -c -C /usr/include opencv2" | tar -x -C include
docker run --rm ecvl bash -c "tar -c -C /usr/local/include yaml-cpp" | tar -x -C include
popd

pyecvl_mount=/pyecvl

docker run --rm -v "${this_dir}":"${pyecvl_mount}" \
  -e BINDER_EXE='/binder/build/llvm-5.0.0/build_5.0.0*/bin/binder' \
  -e ADD_INCLUDE="-I${pyecvl_mount}/third_party/ecvl/modules/core/include -I${pyecvl_mount}/third_party/ecvl/modules/dataset/include -I${pyecvl_mount}/include -I${pyecvl_mount}/src" \
  -w "${pyecvl_mount}"/codegen crs4/binder:135f6e3 ./gen_bindings.sh
cp codegen/bindings/_core.cpp src/
