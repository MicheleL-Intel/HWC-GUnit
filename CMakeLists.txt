#
# Copyright (c) 2016-2017 Kris Jusiak (kris at jusiak dot net)
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 3.5)
project(GUnit-hwc CXX)

option(ENABLE_MEMCHECK "Run the unit tests under valgrind if it is found." OFF)
option(ENABLE_COVERAGE "Run coverage." ON)

add_custom_target(style)
add_custom_command(TARGET style COMMAND find ${CMAKE_CURRENT_LIST_DIR}/benchmark ${CMAKE_CURRENT_LIST_DIR}/example ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/test -iname "*.h" -or -iname "*.cpp" | xargs clang-format -i)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GNU_SOURCE=1 -D_FILE_OFFSET_BITS=64 -DUSE_VK")

if (ENABLE_COVERAGE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
endif()

enable_testing()

include(cmake/googletest.cmake)
fetch_googletest(
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_SOURCE_DIR}/libs/googletest
    )

include_directories(include)
include_directories(SYSTEM
  ${gtest_SOURCE_DIR}/include
  ${gmock_SOURCE_DIR}/include
)

#
# HWC-specific
#
include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/../public)
include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/../os/android)
include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/../../../../../../system/core/include)
include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/../../../../../../external/minigbm/cros_gralloc)
include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/../../../../../../hardware/libhardware/include)
include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/../../../../../../frameworks/native/libs/ui/include)
include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/../../../../../../frameworks/native/libs/nativebase/include)
include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/../../../../../../frameworks/native/libs/arect/include)
include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/../../../../../../vendor/intel/external/project-celadon/hwcomposer/os)
include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/../../../../../../vendor/intel/external/project-celadon/mesa/include)
include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/../../../../../../vendor/intel/external/project-celadon/libdrm/include/drm)


find_program(MEMORYCHECK_COMMAND valgrind)
if (ENABLE_MEMCHECK AND MEMORYCHECK_COMMAND)
  function(test name scenario)
    string(REPLACE "/" "_" out ${name})
    add_executable(${out} ${CMAKE_CURRENT_LIST_DIR}/${name}.cpp)
    add_test(${out} ${MEMORYCHECK_COMMAND} --leak-check=full --error-exitcode=1 ./${out})
    target_link_libraries(${out} gtest_main gmock_main)
    add_custom_command(TARGET ${out} COMMAND ${scenario} ./${out})
  endfunction()
else()
  function(test name scenario)
    string(REPLACE "/" "_" out ${name})
    add_executable(${out} ${CMAKE_CURRENT_LIST_DIR}/${name}.cpp)
    add_test(${out} ./${out})
    target_link_libraries(${out} gtest_main gmock_main)
    add_custom_command(TARGET ${out} COMMAND ${scenario} ./${out})
  endfunction()
endif()

#
# HWC-specific
#
include_directories(unitTest)
test (unitTest/HWCGUnitTest SCENARIO=)

#
# {NOTE: TO DISABLE BASIC EXAMPLES, COMMENT OUT "#[[" and "]]"}
#
#[[
test(example/GMock SCENARIO=)
test(example/GTest SCENARIO=)
test(example/GTest-Lite SCENARIO=)

include_directories(test)
test(test/GMake SCENARIO=)
test(test/GMock SCENARIO=)
test(test/GTest SCENARIO=)
test(test/GTest-Lite SCENARIO=)
test(test/Detail/FileUtils SCENARIO=)
test(test/Detail/Preprocessor SCENARIO=)
test(test/Detail/ProgUtils SCENARIO=)
test(test/Detail/RegexUtils SCENARIO=)
test(test/Detail/StringUtils SCENARIO=)
test(test/Detail/TypeTraits SCENARIO=)
test(test/Detail/Utility SCENARIO=)

include_directories(benchmark)
test(benchmark/GUnit/test SCENARIO=)
test(benchmark/gtest/test SCENARIO=)
]]

#
# {END NOTE}
#

