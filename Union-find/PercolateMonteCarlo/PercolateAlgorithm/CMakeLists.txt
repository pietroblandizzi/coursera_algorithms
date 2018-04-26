# ---------------------------------------------------------------
# * This file is subject to the terms and conditions defined in
# * file 'LICENSE.txt', which is part of this source code package.
# ----------------------------------------------------------------
cmake_minimum_required(VERSION 3.5.0 FATAL_ERROR)
project(percolatealgorithm
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS Off)

add_compile_options(-Wno-error)

include_directories(
include/
)

add_executable(percolatealgorithm
src/percolate.cpp
src/percolate_stats.cpp
main.cpp)

install(TARGETS percolatealgorithm RUNTIME DESTINATION bin)
