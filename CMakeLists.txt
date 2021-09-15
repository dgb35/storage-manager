cmake_minimum_required(VERSION 3.20)
project(storage_manager)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        storage_manager

        src/main.cpp

        src/storage_manager.cpp
        include/storage_manager.hpp
        include/constants.hpp)

set(INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(storage_manager PUBLIC ${INCLUDE_DIRECTORIES})

find_package(Boost 1.66 REQUIRED)
include_directories(${BOOST_SRC_DIR})

add_subdirectory(tests)

