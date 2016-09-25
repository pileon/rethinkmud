find_package(Boost 1.58
        REQUIRED
        COMPONENTS program_options log log_setup
        )

check_include_file_cxx(boost/program_options.hpp HAVE_BOOST_PROGRAM_OPTIONS_HPP)
if(NOT HAVE_BOOST_PROGRAM_OPTIONS_HPP)
    message(FATAL "Need to have Boost Program Options installed")
endif()
