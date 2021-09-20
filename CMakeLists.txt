cmake_minimum_required(VERSION 3.20)
project(storage_manager)

set(CMAKE_CXX_STANDARD 20)

# Options
option(ENABLE_TESTS "Enables tests" OFF)

add_executable(
        storage_manager

        src/example/main.cpp

        src/storage_manager.cpp
        include/storage_manager.hpp
        include/example/constants.hpp
        include/example/sel_event_record.hpp)

set(INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(storage_manager PUBLIC ${INCLUDE_DIRECTORIES})

find_package(Boost COMPONENTS serialization REQUIRED)
include_directories(${BOOST_INCLUDE_DIR})
target_link_libraries(storage_manager Boost::boost Boost::serialization)

if (ENABLE_TESTS)
    add_subdirectory(tests)
endif ()