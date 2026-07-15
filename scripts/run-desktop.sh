#!/usr/bin/env bash
# Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.
#
# Build (if needed) and launch the Fintel IT ForgeCAD desktop CAD modeler.

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
OCCT_INSTALL="${REPO_ROOT}/build/occt-install"
DESKTOP_BUILD="${REPO_ROOT}/build/desktop"

if [[ ! -d "${OCCT_INSTALL}" ]]; then
  echo "OCCT not found at ${OCCT_INSTALL}; building..."
  "${SCRIPT_DIR}/build-occt.sh"
fi

cmake -S "${REPO_ROOT}" -B "${DESKTOP_BUILD}" \
  -DCMAKE_BUILD_TYPE=Release \
  -DFORGECAD_OCCT_INSTALL="${OCCT_INSTALL}" \
  -DCMAKE_PREFIX_PATH="${OCCT_INSTALL};$(brew --prefix qt 2>/dev/null || brew --prefix qt@6 2>/dev/null || true)"

cmake --build "${DESKTOP_BUILD}" --parallel "$(sysctl -n hw.ncpu 2>/dev/null || nproc)"

APP="${DESKTOP_BUILD}/forgecad_desktop"
if [[ ! -x "${APP}" ]]; then
  echo "Expected executable not found: ${APP}" >&2
  exit 1
fi

# Resolve OCCT shared libraries at runtime on macOS.
export DYLD_LIBRARY_PATH="${OCCT_INSTALL}/lib:${DYLD_LIBRARY_PATH:-}"
export CSF_OCCTResourcePath="${OCCT_INSTALL}/share/opencascade/resources"

echo "Launching Fintel IT ForgeCAD..."
exec "${APP}"
