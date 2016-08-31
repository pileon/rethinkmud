include(CheckIncludeFileCXX)

check_include_file_cxx(rethinkdb.h HAVE_RETHINKDB_H)
if(NOT HAVE_RETHINKDB_H)
    message(FATAL "the <rethinkdb.h> header file is required")
endif()

#find_library(
#
#)
