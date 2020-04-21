#!/usr/bin/env bash

set -euo pipefail

docker build -t ecvl -f Dockerfile.ecvl .
docker build -t pyecvl .
docker build -t pyecvl-docs -f Dockerfile.docs .
rm -rf /tmp/html && docker run --rm pyecvl-docs bash -c "tar -c -C /docs/_build html" | tar -x -C /tmp
