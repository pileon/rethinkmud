configure_file(${CMAKE_SOURCE_DIR}/src/include/autoconf.h.in ${CMAKE_SOURCE_DIR}/src/include/autoconf.h)

set(SOURCE_FILES main.cpp config.cpp config.h)
add_executable(rethinkmud ${SOURCE_FILES})
target_include_directories(rethinkmud
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

check_cxx_compiler_flag(-Wno-vla-extension HAVE_FLAG_WNO_VLA_EXTENSION)
if(HAVE_FLAG_WNO_VLA_EXTENSION)
    target_compile_options(rethinkmud PRIVATE -Wno-vla-extension)
endif()

add_dependencies(rethinkmud librethinkdbxx)
target_link_libraries(rethinkmud ${CMAKE_BINARY_DIR}/rethinkdbxx/librethinkdb++.a ${LIBICU_LIBRARIES})

#if(HAVE_LIBCXXABI AND NOT STDLIBCXX_WITHOUT_LIBCXXABI)
    target_link_libraries(rethinkmud c++abi)
#endif()

add_subdirectory(net)

target_link_libraries(rethinkmud network)
target_link_libraries(rethinkmud Boost::program_options)
