# Check for supported warning flags
check_cxx_compiler_flag(-Wall HAVE_FLAG_WALL)
if(HAVE_FLAG_WALL)
    list(APPEND COMPILER_OPTIONS -Wall)
endif()
check_cxx_compiler_flag(-Wextra HAVE_FLAG_WEXTRA)
if(HAVE_FLAG_WEXTRA)
    list(APPEND COMPILER_OPTIONS -Wextra)
endif()
check_cxx_compiler_flag(-Weffc++ HAVE_FLAG_WEFFCXX)
if(HAVE_FLAG_WEFFCXX)
    list(APPEND COMPILER_OPTIONS -Weffc++)
endif()
check_cxx_compiler_flag(-Wpedantic HAVE_FLAG_WPEDANTIC)
if(HAVE_FLAG_WPEDANTIC)
    list(APPEND COMPILER_OPTIONS -Wpedantic)
else()
    check_cxx_compiler_flag(-pedantic HAVE_FLAG_PEDANTIC)
    if(HAVE_FLAG_PEDANTIC)
        list(APPEND COMPILER_OPTIONS -pedantic)
    endif()
endif()
check_cxx_compiler_flag(-Wimplicit-fallthrough HAVE_FLAG_WIMPLICIT_FALLTHROUGH)
if(HAVE_FLAG_WIMPLICIT_FALLTHROUGH)
    list(APPEND COMPILER_OPTIONS -Wimplicit-fallthrough)
endif()

# Check for standard to use
check_cxx_compiler_flag(-std=c++17 HAVE_FLAG_STD_CXX17)
if(HAVE_FLAG_STD_CXX17)
    list(APPEND COMPILER_OPTIONS -std=c++17)
else()
    check_cxx_compiler_flag(-std=c++1z HAVE_FLAG_STD_CXX1Z)
    if(HAVE_FLAG_STD_CXX1Z)
        list(APPEND COMPILER_OPTIONS -std=c++1z)
    else()
        message(FATAL " Need a compiler capable of at least C++1z (the upcomming C++17 standard)")
    endif()
endif()

check_cxx_compiler_flag(-stdlib=libc++ HAVE_FLAG_STDLIB_LIBCXX)

if(HAVE_FLAG_STDLIB_LIBCXX)
    message(STATUS "Looking for libc++")
    find_library(HAVE_LIBCXX c++)
    if(NOT HAVE_LIBCXX)
        message(FATAL "Need libc++")
    endif()
    message(STATUS "Looking for libc++ - found")

    # Check for the ABI library, and if we can build with `-stdlib=libc++` without linking with `-lc++abi`
    message(STATUS "Looking for libc++abi")
    find_library(HAVE_LIBCXXABI c++abi)
    if(NOT HAVE_LIBCXXABI)
        message(STATUS "Looking for libc++abi - not found")
    else()
        message(STATUS "Looking for libc++abi - found")
        set(OLD_CMAKE_REQUIRED_FLAGS ${CMAKE_REQUIRED_FLAGS})
        set(CMAKE_REQUIRED_FLAGS "-stdlib=libc++")
        CHECK_CXX_SOURCE_COMPILES(
                "#include <iostream>
            int main()
            {
                std::cout << 'x';
            }"
                STDLIBCXX_WITHOUT_LIBCXXABI
                FAIL_REGEX "libc\\\\+\\\\+abi\\\\.so")
        set(CMAKE_REQUIRED_FLAGS ${OLD_CMAKE_REQUIRED_FLAGS})
    endif()
endif()

if(HAVE_FLAG_STDLIB_LIBCXX)
    list(APPEND COMPILER_OPTIONS -stdlib=libc++)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
endif()

# Check for other miscelaneous flags
check_cxx_compiler_flag(-pipe HAVE_FLAG_PIPE)
if(HAVE_FLAG_PIPE)
    list(APPEND COMPILER_OPTIONS -pipe)
endif()

if(Threads_FOUND)
    check_cxx_compiler_flag(-pthread HAVE_FLAG_PTHREAD)
    if(HAVE_FLAG_PTHREAD)
        list(APPEND COMPILER_OPTIONS -pthread)
    endif()
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
    # TODO: Add the pthread linker library?
    # TODO: Check if it is needed first
endif()
