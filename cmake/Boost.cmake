find_package(Boost 1.61
        REQUIRED
        COMPONENTS system)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

    set(temp_CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
    foreach(boostlib IN LISTS Boost_LIBRARIES)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${boostlib}")
    endforeach()
    check_include_file_cxx(boost/asio.hpp HAVE_BOOST_ASIO_HPP)
    set(CMAKE_EXE_LINKER_FLAGS "${temp_CMAKE_EXE_LINKER_FLAGS}")
endif()
