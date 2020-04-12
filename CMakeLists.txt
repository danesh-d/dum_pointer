cmake_minimum_required(VERSION 3.0.0)
project (DumPointer)

find_package(GTest REQUIRED)

add_library(DumPointer INTERFACE)
target_include_directories(DumPointer
  INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(test)
