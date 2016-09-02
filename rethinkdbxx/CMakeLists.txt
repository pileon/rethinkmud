set(librethinkdbxx_CXX_CLAGS ${COMPILER_OPTIONS} -Ibuild/gen)
if(CMAKE_DEBUG_BUILD)
    set(librethinkdbxx_CXX_CLAGS ${librethinkdbxx_CXX_CLAGS} ${CMAKE_CXX_FLAGS_DEBUG})
endif()
if(CMAKE_RELEASE_BUILD)
    set(librethinkdbxx_CXX_CLAGS ${librethinkdbxx_CXX_CLAGS} ${CMAKE_CXX_FLAGS_RELEASE})
endif()

add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/rethinkdbxx/librethinkdb++.a ${CMAKE_CURRENT_SOURCE_DIR}/rethinkdb.h
        COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/librethinkdbxx && make CXX=${CMAKE_CXX_COMPILER} CXXFLAGS="${librethinkdbxx_CXX_CLAGS}" build/librethinkdb++.a build/include/rethinkdb.h
        COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/librethinkdbxx/build/librethinkdb++.a .
        COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/librethinkdbxx/build/include/rethinkdb.h ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_target(librethinkdbxx
        DEPENDS ${CMAKE_BINARY_DIR}/rethinkdbxx/librethinkdb++.a ${CMAKE_CURRENT_SOURCE_DIR}/rethinkdb.h)
