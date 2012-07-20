cmake_minimum_required (VERSION 2.6)
project (OPTIMAL_TAX)
# The version number.
set (OPTIMAL_TAX_VERSION_MAJOR 1)
set (OPTIMAL_TAX_VERSION_MINOR 0)

set(PLATFORM 64)
 
set(CMAKE_CXX_FLAGS "-g -Wall -O3 -funroll-loops -ftree-vectorize -msse3")

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /opt/local/lib)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(BOOST_LIB_PREFIX "lib")
set(Boost_LIB_PREFIX "lib")
set(BOOST_COMPILER "-vc100")
set(Boost_COMPILER "-vc100")
set(Boost_ADDITIONAL_VERSIONS "1.47" "1.47.0")

find_package(Boost REQUIRED system filesystem)

add_subdirectory(tao)

include_directories (${PROJECT_SOURCE_DIR}/tao/evolutionary_algorithms)
include_directories (${PROJECT_SOURCE_DIR}/tao/synchronous_algorithms)
include_directories (${PROJECT_SOURCE_DIR}/tao/undvc_common)
include_directories (${Boost_INCLUDE_DIR})


add_executable(EconMrsyx econ_mrsyx)
target_link_libraries(EconMrsyx undvc_common EvolutionaryAlgorithms SynchronousAlgorithms undvc_common ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})

add_subdirectory(multi_objective)

add_executable(Elasticities elasticities)
target_link_libraries(Elasticities multi_objective EvolutionaryAlgorithms SynchronousAlgorithms undvc_common ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
