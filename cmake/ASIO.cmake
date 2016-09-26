check_include_file_cxx(asio.hpp HAVE_ASIO_HPP)
if(NOT HAVE_ASIO_HPP)
    error("Need to have ASIO installed")
endif()
