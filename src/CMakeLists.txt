configure_file(${CMAKE_SOURCE_DIR}/src/include/autoconf.h.in ${CMAKE_SOURCE_DIR}/src/include/autoconf.h)

set(SOURCE_FILES main.cpp config.cpp include/config.h include/rethinkdbxx.h include/rethinkmud.h log.cpp include/log.h)
add_executable(rethinkmud ${SOURCE_FILES})
target_include_directories(rethinkmud
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

#check_cxx_compiler_flag(-Wno-vla-extension HAVE_FLAG_WNO_VLA_EXTENSION)
#if(HAVE_FLAG_WNO_VLA_EXTENSION)
#    target_compile_options(rethinkmud PRIVATE -Wno-vla-extension)
#endif()
#check_cxx_compiler_flag(-Wno-vla HAVE_FLAG_WNO_VLA)
#if(HAVE_FLAG_WNO_VLA)
#    target_compile_options(rethinkmud PRIVATE -Wno-vla)
#endif()

add_subdirectory(net)

target_compile_options(rethinkmud PRIVATE ${COMPILER_OPTIONS})
target_compile_definitions(rethinkmud PRIVATE BOOST_LOG_DYN_LINK)

add_dependencies(rethinkmud librethinkdbxx)

target_link_libraries(rethinkmud network)
target_link_libraries(rethinkmud ${CMAKE_BINARY_DIR}/rethinkdbxx/librethinkdb++.a)

target_link_libraries(rethinkmud ${LIBICU_LIBRARIES})
target_link_libraries(rethinkmud Boost::program_options Boost::log_setup Boost::log)

#if(HAVE_LIBCXXABI AND NOT STDLIBCXX_WITHOUT_LIBCXXABI)
    target_link_libraries(rethinkmud c++abi)
#endif()
