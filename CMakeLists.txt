# 以下のページとetrobocon2021を参考にいくつか変更
# https://github.com/google/googletest/blob/main/googletest/README.md

cmake_minimum_required(VERSION 2.8.2)
set(PROJECT_NAME_STR etrobocon2022)
project(${PROJECT_NAME_STR})

# make sure that we have support for C++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

set(CMAKE_CXX_FLAGS "-g")

if(COMPILER_SUPPORTS_CXX17)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -std=c++17")
elseif(COMPILER_SUPPORTS_CXX14)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -std=c++14")
elseif(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -std=c++0x")
else()
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# Download and unpack googletest at configure time
configure_file(test/CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)

if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)

if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
  ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
  EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if(CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

# Now simply link against gtest or gtest_main as needed. Eg
# -------------------
# Module source
# -------------------
# Google Test のために、ヘッダファイルのあるディレクトリを指定する？
include_directories(${PROJECT_SOURCE_DIR}/module)
include_directories(${PROJECT_SOURCE_DIR}/test/dummy)
include_directories(${PROJECT_SOURCE_DIR}/module/API)
include_directories(${PROJECT_SOURCE_DIR}/module/Motion)
include_directories(${PROJECT_SOURCE_DIR}/module/GameMotion)
include_directories(${PROJECT_SOURCE_DIR}/module/common)
include_directories(${GTEST_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/module)
file(GLOB SRC_FILES
  ${PROJECT_SOURCE_DIR}/module/*.cpp
  ${PROJECT_SOURCE_DIR}/module/*/*.cpp
  ${PROJECT_SOURCE_DIR}/test/dummy/*.cpp
)
add_library(etrobocon2022_impl ${SRC_FILES})

# -------------------
# Test
# -------------------
enable_testing()
file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)

add_executable(etrobocon2022_test ${TEST_SRC_FILES} ${SRC_FILES})
target_link_libraries(etrobocon2022_test gtest_main)
add_test(test1 etrobocon2022_test)
