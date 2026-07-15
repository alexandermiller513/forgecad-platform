#!/usr/bin/env bash
# Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.
#
# Build the proprietary OCCT adapter layer (dynamic linking to OCCT).

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
BUILD_DIR="${REPO_ROOT}/build/desktop"
OCCT_INSTALL="${REPO_ROOT}/build/occt-install"

if [[ ! -d "${OCCT_INSTALL}" ]]; then
  echo "OCCT not found; run scripts/build-occt.sh first." >&2
  exit 1
fi

cmake -S "${REPO_ROOT}" -B "${BUILD_DIR}" \
  -DCMAKE_BUILD_TYPE=Release \
  -DFORGECAD_OCCT_INSTALL="${OCCT_INSTALL}" \
  -DCMAKE_PREFIX_PATH="${OCCT_INSTALL};$(brew --prefix qt 2>/dev/null || brew --prefix qt@6 2>/dev/null || true)"

cmake --build "${BUILD_DIR}" --target forgecad_occt_adapter --parallel "$(sysctl -n hw.ncpu 2>/dev/null || nproc)"

echo "OCCT adapter built in ${BUILD_DIR}"
