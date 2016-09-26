set(SOURCE_FILES ../include/net/server.h network.cpp ../include/net/network.h ../include/net/tcp.h ../include/net/telnet.h ../include/net/ip.h ../include/net/connection.h telnet.cpp)
add_library(network STATIC ${SOURCE_FILES})
target_include_directories(network
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
set_target_properties(network PROPERTIES LINKER_LANGUAGE CXX)

add_executable(net-test net-test.cpp ../config.cpp ../log.cpp)
target_include_directories(net-test
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_libraries(net-test network ${LIBICU_LIBRARIES})
#if(HAVE_LIBCXXABI AND NOT STDLIBCXX_WITHOUT_LIBCXXABI)
    target_link_libraries(net-test c++abi)
#endif()
target_link_libraries(net-test Boost::program_options Boost::log_setup Boost::log)
