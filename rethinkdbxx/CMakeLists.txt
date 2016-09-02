set(REQL ${CMAKE_CURRENT_SOURCE_DIR}/librethinkdbxx/reql)
set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/librethinkdbxx/src)

set(LIBRETHINKDBXX_SOURCES
        librethinkdbxx/src/connection.cc
        librethinkdbxx/src/datum.cc
        librethinkdbxx/src/json.cc
        librethinkdbxx/src/term.cc
        librethinkdbxx/src/cursor.cc
        librethinkdbxx/src/types.cc
        librethinkdbxx/src/utils.cc
        )

add_custom_command(OUTPUT ${SRC}/protocol_defs.h
        COMMAND python3 ${REQL}/gen.py ${REQL}/ql2.proto > ${SRC}/protocol_defs.h
        )
add_custom_target(protocol_defs DEPENDS ${SRC}/protocol_defs.h)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/rethinkdb.h
        COMMAND echo "// Auto-generated file, built from build/gen/protocol_defs.h src/utils.h src/error.h src/exceptions.h src/types.h src/datum.h src/connection.h src/cursor.h src/term.h" > ${CMAKE_CURRENT_SOURCE_DIR}/rethinkdb.nodocs.h
        COMMAND echo '\#pragma once' >> ${CMAKE_CURRENT_SOURCE_DIR}/rethinkdb.nodocs.h
        COMMAND cat ${SRC}/protocol_defs.h ${SRC}/utils.h ${SRC}/error.h ${SRC}/exceptions.h ${SRC}/types.h ${SRC}/datum.h ${SRC}/connection.h ${SRC}/cursor.h ${SRC}/term.h | grep -v '^\#pragma once' | grep -v '^\#include \"' >> ${CMAKE_CURRENT_SOURCE_DIR}/rethinkdb.nodocs.h
        COMMAND python3 ${REQL}/add_docs.py ${REQL}/python_docs.txt < ${CMAKE_CURRENT_SOURCE_DIR}/rethinkdb.nodocs.h >> ${CMAKE_CURRENT_SOURCE_DIR}/rethinkdb.h
        DEPENDS ${SRC}/protocol_defs.h
        )
add_custom_target(rethinkdb_header DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/rethinkdb.h)

add_library(rethinkdbxx STATIC ${LIBRETHINKDBXX_SOURCES})
set_target_properties(rethinkdbxx PROPERTIES LINKER_LANGUAGE CXX)
add_dependencies(rethinkdbxx protocol_defs rethinkdb_header)
