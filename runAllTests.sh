#!/bin/sh
# benchmark
echo -e "\e[34mBlue Running benchmark_GUnit_test"
./out/benchmark_GUnit_test
echo Running "benchmark_gtest_test"
./out/benchmark_gtest_test

# examples
echo Running "example_GMock"
./out/example_GMock
echo Running "example_GTest"
./out/example_GTest
echo Running "example_GTest-Lite"
./out/example_GTest-Lite

# test
./out/test_Detail_FileUtils
./out/test_Detail_Preprocessor
./out/test_Detail_ProgUtils
./out/test_Detail_RegexUtils
./out/test_Detail_StringUtils
./out/test_Detail_TypeTraits
./out/test_Detail_Utility
./out/test_GMake
./out/test_GMock
./out/test_GTest
./out/test_GTest-Lite
