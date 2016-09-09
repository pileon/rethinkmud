include(CheckCXXCompilerFlag)

check_cxx_compiler_flag(-D_DEBUG HAVE_FLAG_D)
if(HAVE_FLAG_D)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
endif()
check_cxx_compiler_flag(-O0 HAVE_FLAG_O0)
if(HAVE_FLAG_O0)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "^(GNU)|(Clang)$")
    include(cmake/BuildFlags-clang-gcc.cmake)
else()
    # TODO: Most likely VC++, check for that an include the correct file for it
endif()

add_compile_options(${COMPILER_OPTIONS})
string(REPLACE ";" " " CMAKE_REQUIRED_FLAGS "${COMPILER_OPTIONS}")
