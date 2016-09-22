#include "autoconf.h"
#include "config.h"

#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>

namespace po = boost::program_options;

namespace rethinkmud
{
    namespace config
    {
        /**
         * \brief Default values for configuration options
         */
        namespace default_values
        {
            constexpr unsigned short port = 4000;
        }

        /////////////////////////////////////////////////////////////

        namespace
        {
            po::variables_map config_vm;

            auto get_command_line_options(std::string const &argv0)
            {
                std::string default_config_file = argv0 + ".cfg";

                po::options_description options{"General options"};
                options.add_options()
                    ("help,h", "show help message")
                    ("version,v", "show program version")
                    ("config,c", po::value<std::string>()->default_value(default_config_file), "configuration file");

                return options;
            }

            auto get_config_options()
            {
                po::options_description config;
                return config;
            }

            auto get_common_options()
            {
                po::options_description common{"Common options"};
                common.add_options()
                    ("port,p", po::value<int>()->default_value(default_values::port), "main port number");

                return common;
            }
        }

        void load(int argc, char* argv[])
        {
            auto options = get_command_line_options(argv[0]);
            auto config = get_config_options();
            auto common = get_common_options();

            options.add(common);
            config.add(common);

            try
            {
                po::store(po::parse_command_line(argc, argv, options), config_vm, true);
            }
            catch (po::error& e)
            {
                std::clog << "Error: " << e.what() << '\n';
                std::clog << "Error: Use '" << argv[0] << " --help' to get help about command line options\n";
                std::exit(1);
            }

            po::notify(config_vm);

            if (config_vm.count("help"))
            {
                std::cout << options << '\n';
                std::exit(0);
            }

            if (config_vm.count("version"))
            {
                std::cout << "RethinkMUD version " << RETHINKMUD_VERSION << '\n';
                std::exit(0);
            }

            std::ifstream config_file{config_vm["config"].as<std::string>()};
            if (config_file)
            {
                try
                {
                    po::store(po::parse_config_file(config_file, config), config_vm, true);
                }
                catch (po::error& e)
                {
                    std::clog << "Error: " << e.what() << '\n';
                    std::exit(1);
                }
            }

            // TODO: Environment variables?

        }

        template<typename T>
        T get(std::string name)
        {
            return config_vm[name].as<T>();
        }
    }
}
