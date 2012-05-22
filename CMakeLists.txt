cmake_minimum_required (VERSION 2.6)
project (OPTIMAL_TAX)
# The version number.
set (OPTIMAL_TAX_VERSION_MAJOR 1)
set (OPTIMAL_TAX_VERSION_MINOR 0)
 
set(CMAKE_CXX_FLAGS "-g -Wall -O3 -funroll-loops -ftree-vectorize -msse3")

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /opt/local/lib)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(Boost REQUIRED)

add_subdirectory(tao)

include_directories (${PROJECT_SOURCE_DIR}/tao/evolutionary_algorithms)
include_directories (${PROJECT_SOURCE_DIR}/tao/deterministic_algorithms)
include_directories (${PROJECT_SOURCE_DIR}/tao/undvc_common)
include_directories (${Boost_INCLUDE_DIR})

add_executable(EconMrsyx econ_mrsyx)
target_link_libraries(EconMrsyx undvc_common EvolutionaryAlgorithms DeterministicAlgorithms undvc_common)
