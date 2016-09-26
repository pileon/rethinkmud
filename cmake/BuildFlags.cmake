include(CheckCXXCompilerFlag)

if(CMAKE_CXX_COMPILER_ID MATCHES "^(GNU)|(Clang)$")
    include(cmake/BuildFlags-clang-gcc.cmake)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "^MSVC$")
    # TODO: Implement this sometime
    # include(cmake/BuildFlags-msvc.cmake)
else()
    message(WARNING "Unknown compiler, do not know how to test for specific flags")
endif()

#add_compile_options(${COMPILER_OPTIONS})
#string(REPLACE ";" " " CMAKE_REQUIRED_FLAGS "${COMPILER_OPTIONS}")
