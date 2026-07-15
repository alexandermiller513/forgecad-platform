#!/usr/bin/env bash
# Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.
#
# Build the proprietary OCCT adapter layer (dynamic linking to OCCT).

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
BUILD_DIR="${REPO_ROOT}/build/occt-adapter"
OCCT_INSTALL="${REPO_ROOT}/build/occt-install"

cmake -S "${REPO_ROOT}/proprietary/occt-adapter" -B "${BUILD_DIR}" \
  -DCMAKE_BUILD_TYPE=Release \
  -DOpenCASCADE_DIR="${OCCT_INSTALL}/cmake"

cmake --build "${BUILD_DIR}" --parallel "$(sysctl -n hw.ncpu 2>/dev/null || nproc)"

echo "OCCT adapter built in ${BUILD_DIR}"
