cmake_minimum_required(VERSION 3.5)
project(rethinkmud
        VERSION 0.2.0
        LANGUAGES CXX C)

find_package(Threads)

include(CheckIncludeFileCXX)

include(cmake/BuildFlags.cmake)
include(cmake/ASIO.cmake)
include(cmake/ICU.cmake)
include(cmake/Boost.cmake)
include(cmake/RapidJSON.cmake)

add_subdirectory(rethinkdbxx)
add_subdirectory(src)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
