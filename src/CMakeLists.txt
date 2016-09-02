configure_file(${CMAKE_SOURCE_DIR}/src/include/autoconf.h.in ${CMAKE_SOURCE_DIR}/src/include/autoconf.h)

set(SOURCE_FILES main.cpp)
add_executable(rethinkmud ${SOURCE_FILES})
target_include_directories(rethinkmud
        PRIVATE include)

target_link_libraries(rethinkmud rethinkdbxx)
