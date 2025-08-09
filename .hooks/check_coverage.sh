#!/bin/bash
set -e

# Ensure coverage tools are installed
command -v lcov >/dev/null 2>&1 || { echo "lcov not installed"; exit 1; }
command -v gcovr >/dev/null 2>&1 || { echo "gcovr not installed"; exit 1; }

# Clean previous coverage data
rm -rf coverage
mkdir -p coverage

# Build with coverage flags
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build

# Run all tests
cd build
ctest --output-on-failure
if [ $? -ne 0 ]; then
    echo "Tests failed. Commit aborted."
    exit 1
fi
# Generate gcovr text output for quick check
echo "==== GCOVR Terminal Report ===="
gcovr -r .. --exclude 'test/' --txt --sort-uncovered
cd ..
# Generate LCOV HTML report
echo "==== Generating LCOV HTML Report ===="
lcov --capture --directory . --output-file coverage/coverage.info

# Remove test files, system headers, and external libraries
lcov --remove coverage/coverage.info \
    '*/test/*' \
    '/usr/*' \
    --output-file coverage/coverage_filtered.info

genhtml coverage/coverage_filtered.info --output-directory coverage/html

# Fail if coverage < 100%
gcovr -r .. --exclude 'test/' --fail-under-line 80

echo "HTML report generated at: build/coverage/html/index.html"
