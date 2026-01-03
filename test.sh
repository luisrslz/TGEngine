#!/bin/bash
set -e

cmake -S . -B build_tests -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON
cmake --build build_tests

cd build_tests/tests
ctest --output-on-failure

