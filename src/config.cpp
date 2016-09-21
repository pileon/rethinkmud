//
// Created by arrow on 9/21/16.
//

#include "autoconf.h"
#include "config.h"

#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

namespace rethinkmud
{
    namespace config
    {
        void load(int argc, char** argv)
        {
            po::options_description general{"General options"};
            general.add_options()
                ("help", "show help message")
                ("version", "show program version");

            po::variables_map vm;
            po::store(po::parse_command_line(argc, argv, general), vm, true);

            if (vm.count("help"))
            {
                std::cout << general << '\n';
                exit(0);
            }

            if (vm.count("version"))
            {
                std::cout << "RethinkMUD version " << RETHINKMUD_VERSION << '\n';
                exit(0);
            }
        }
    }
}
