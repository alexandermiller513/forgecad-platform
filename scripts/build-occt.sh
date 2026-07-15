#!/usr/bin/env bash
# Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.
#
# Build Open CASCADE Technology from third-party/occt.
# OCCT remains an isolated LGPL dependency — do not add proprietary code here.

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
OCCT_SRC="${REPO_ROOT}/third-party/occt"
BUILD_DIR="${REPO_ROOT}/build/occt"
INSTALL_DIR="${REPO_ROOT}/build/occt-install"

mkdir -p "${BUILD_DIR}"

cmake -S "${OCCT_SRC}" -B "${BUILD_DIR}" \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX="${INSTALL_DIR}" \
  -DBUILD_LIBRARY_TYPE=Shared

cmake --build "${BUILD_DIR}" --parallel "$(sysctl -n hw.ncpu 2>/dev/null || nproc)"
cmake --install "${BUILD_DIR}"

echo "OCCT installed to ${INSTALL_DIR}"
