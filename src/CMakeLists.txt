configure_file(${CMAKE_SOURCE_DIR}/src/include/autoconf.h.in ${CMAKE_SOURCE_DIR}/src/include/autoconf.h)

set(SOURCE_FILES main.cpp)
add_executable(rethinkmud ${SOURCE_FILES})
target_include_directories(rethinkmud
        PRIVATE include)

add_dependencies(rethinkmud librethinkdbxx)
target_link_libraries(rethinkmud ${CMAKE_BINARY_DIR}/rethinkdbxx/librethinkdb++.a)

if(NOT STDLIBCXX_WITHOUT_LIBCXXABI)
    target_link_libraries(rethinkmud c++abi)
endif()
