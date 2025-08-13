#!/usr/bin/env bash
set -euo pipefail

PROJECT_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
BUILD_DIR="${PROJECT_ROOT}/build"
COVER_DIR="${BUILD_DIR}/coverage"
COVERAGE_MIN="${COVERAGE_MIN:-80}"   # change to 100 if you want strict

# Tools check
command -v gcovr >/dev/null || { echo "gcovr not installed"; exit 1; }
command -v lcov  >/dev/null || { echo "lcov not installed";  exit 1; }
command -v genhtml >/dev/null || { echo "genhtml (lcov) not installed"; exit 1; }

# Clean coverage artifacts
mkdir -p "${BUILD_DIR}"
find "${BUILD_DIR}" -name "*.gcda" -delete || true
rm -rf "${COVER_DIR}"
mkdir -p "${COVER_DIR}"

# Configure & build with coverage
cmake -S "${PROJECT_ROOT}" -B "${BUILD_DIR}" \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_C_FLAGS="--coverage -O0 -g" \
  -DCMAKE_CXX_FLAGS="--coverage -O0 -g"
cmake --build "${BUILD_DIR}"

# Run tests (serialize to avoid file races)
ctest --test-dir "${BUILD_DIR}" --output-on-failure -j1

echo "==== GCOVR Terminal Report ===="
# IMPORTANT: point gcovr at the build dir for object files and the project root for sources
gcovr \
  --root "${PROJECT_ROOT}" \
  --object-directory "${BUILD_DIR}" \
  --exclude 'test/' \
  --txt --sort-uncovered

echo "==== Enforcing coverage >= ${COVERAGE_MIN}% ===="
gcovr \
  --root "${PROJECT_ROOT}" \
  --object-directory "${BUILD_DIR}" \
  --exclude 'test/' \
  --fail-under-line "${COVERAGE_MIN}"

echo "==== Generating LCOV HTML Report ===="
# Capture from build dir
lcov --capture --directory "${BUILD_DIR}" --output-file "${COVER_DIR}/coverage.info"
# Filter out tests and system headers
lcov --remove "${COVER_DIR}/coverage.info" '*/test/*' '/usr/*' \
     --output-file "${COVER_DIR}/coverage_filtered.info"
genhtml "${COVER_DIR}/coverage_filtered.info" --output-directory "${COVER_DIR}/html"

echo "HTML report: ${COVER_DIR}/html/index.html"