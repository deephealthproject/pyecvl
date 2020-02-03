#!/usr/bin/env bash

set -euo pipefail

this="${BASH_SOURCE-$0}"
this_dir=$(cd -P -- "$(dirname -- "${this}")" && pwd -P)

pushd "${this_dir}"
pushd third_party/ecvl
ecvl_rev=$(git rev-parse --short HEAD)
popd
docker build -t simleo/ecvl:${ecvl_rev} -f Dockerfile.ecvl .
docker build -f Dockerfile.jenkins --build-arg ecvl_rev=${ecvl_rev} -t simleo/pyecvl-base:${ecvl_rev} .
popd
