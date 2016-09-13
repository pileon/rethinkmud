set(SOURCE_FILES ../include/net/server.h)
add_library(network STATIC ${SOURCE_FILES})
target_include_directories(network
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
set_target_properties(network PROPERTIES LINKER_LANGUAGE CXX)

add_executable(net-test net-test.cpp)
target_include_directories(net-test
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_libraries(net-test Boost::system network)
if(NOT STDLIBCXX_WITHOUT_LIBCXXABI)
    target_link_libraries(net-test c++abi)
endif()
