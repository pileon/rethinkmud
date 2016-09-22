//
// Created by arrow on 9/21/16.
//

#include "autoconf.h"
#include "config.h"

#include <boost/program_options.hpp>
#include <iostream>
#include <cstdlib>

namespace po = boost::program_options;

namespace rethinkmud
{
    namespace config
    {
        namespace
        {
            po::options_description get_command_line_options(std::string const &argv0)
            {
                std::string default_config_file = argv0 + ".cfg";

                po::options_description general{"General options"};
                general.add_options()
                    ("help,h", "show help message")
                    ("version,v", "show program version")
                    ("config,c", po::value<std::string>()->default_value(default_config_file), "configuration file");

                po::options_description options;
                return options.add(general);
            }
        }

        void load(int argc, char* argv[])
        {
            auto options = get_command_line_options(argv[0]);
            //auto config = get_config_options();
            //auto common = get_common_options();

            //options.add(common);
            //config.add(common);

            po::variables_map vm;

            try
            {
                po::store(po::parse_command_line(argc, argv, options), vm, true);
            }
            catch (po::error& e)
            {
                std::clog << "Error: " << e.what() << '\n';
                std::clog << "Error: Use '" << argv[0] << " --help' to get help about command line options\n";
                std::exit(1);
            }

            po::notify(vm);

            if (vm.count("help"))
            {
                std::cout << options << '\n';
                std::exit(0);
            }

            if (vm.count("version"))
            {
                std::cout << "RethinkMUD version " << RETHINKMUD_VERSION << '\n';
                std::exit(0);
            }

            std::cout << "Configuration file = " << vm["config"].as<std::string>() << '\n';

            //try
            //{
            //    po::store(po::parse_command_line(argc, argv, config), vm, true);
            //}
            //catch (po::error& e)
            //{
            //    std::clog << "Error: " << e.what() << '\n';
            //    std::exit(1);
            //}

        }
    }
}
