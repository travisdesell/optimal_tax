cmake_minimum_required (VERSION 2.6)
project (OPTIMAL_TAX)
# The version number.
set (OPTIMAL_TAX_VERSION_MAJOR 1)
set (OPTIMAL_TAX_VERSION_MINOR 0)

set(PLATFORM 64)
 
set(CMAKE_CXX_FLAGS "-g -Wall -O3 -funroll-loops -ftree-vectorize -msse3")

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /opt/local/lib)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/tao/undvc_common/cmake/Modules/")

set(BOOST_LIB_PREFIX "lib")
set(Boost_LIB_PREFIX "lib")
set(BOOST_COMPILER "-vc100")
set(Boost_COMPILER "-vc100")
set(Boost_ADDITIONAL_VERSIONS "1.47" "1.47.0")

find_package(Boost REQUIRED system filesystem)
find_package(MySQL)

add_subdirectory(tao)

#include_directories (${PROJECT_SOURCE_DIR}/tao/evolutionary_algorithms)
#include_directories (${PROJECT_SOURCE_DIR}/tao/synchronous_algorithms)
#include_directories (${PROJECT_SOURCE_DIR}/tao/undvc_common)
include_directories (${PROJECT_SOURCE_DIR}/tao)
include_directories (${Boost_INCLUDE_DIR})


add_executable(EconMrsyx econ_mrsyx)
target_link_libraries(EconMrsyx undvc_common asynchronous_algorithms synchronous_algorithms tao_util)

add_subdirectory(multi_objective)

add_executable(Elasticities elasticities)
target_link_libraries(Elasticities multi_objective undvc_common asynchronous_algorithms synchronous_algorithms tao_util)

add_subdirectory(government_problem)

add_executable(SecondStage second_stage)
target_link_libraries(SecondStage government_problem undvc_common asynchronous_algorithms synchronous_algorithms tao_util)

add_executable(SecondStageExt second_stageext)
target_link_libraries(SecondStageExt government_problem undvc_common asynchronous_algorithms synchronous_algorithms tao_util) 

if (MYSQL_FOUND)
    include_directories(${MYSQL_INCLUDE_DIR})

    add_executable(SecondStageDB second_stage_db)
    target_link_libraries(SecondStageDB government_problem undvc_common asynchronous_algorithms synchronous_algorithms tao_util db_asynchronous_algorithms ${MYSQL_LIBRARIES})
endif (MYSQL_FOUND)
