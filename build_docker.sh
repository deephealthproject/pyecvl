#!/usr/bin/env bash

set -euo pipefail

docker build -t ecvl -f Dockerfile.ecvl .
