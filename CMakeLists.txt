cmake_minimum_required(VERSION 3.6)
project(rethinkmud
        VERSION 0.0.1
        LANGUAGES CXX C)

find_package(Threads)

include(cmake/BuildFlags.cmake)

add_subdirectory(rethinkdbxx)
add_subdirectory(src)

#if(BUILD_TESTS)
#    enable_testing()
#    add_subdirectory(tests)
#endif()
