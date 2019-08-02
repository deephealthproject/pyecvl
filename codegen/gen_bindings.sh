#!/bin/bash

set -euo pipefail

this="${BASH_SOURCE:-$0}"
this_dir=$(cd -P -- "$(dirname -- "${this}")" && pwd -P)

# this refers to the crs4/binder docker container
binder=${BINDER_EXE:-/binder/build/llvm-4.0.0/build_4.0.0*/bin/binder}

# e.g., -I../third_party/ecvl/modules/core/include -I/foo
add_inc=${ADD_INCLUDE:-}

rm -rf ./bindings/ && mkdir bindings/
${binder} \
  --root-module _core \
  --prefix "${this_dir}"/bindings/ \
  --bind ecvl \
  --config config.cfg \
  --single-file \
  all_includes.hpp \
  -- -std=c++14 \
  ${add_inc} \
  -DNDEBUG
