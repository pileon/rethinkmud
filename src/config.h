#ifndef RETHINKMUD_CONFIG_H
#define RETHINKMUD_CONFIG_H

#include <string>
#include <boost/program_options/variables_map.hpp>

namespace rethinkmud
{
    /**
     * \brief Namespace containing command line argument and configuration file management
     */
    namespace config
    {
        /**
         * \brief Parse command line options and configuration file
         * \param argc argc from the main function
         * \param argv argv from the main function
         */
        void load(int argc, char* argv[]);

        /**
         * \brief Get the configuration internal variables map
         * \return the variables map
         * \private
         */
        boost::program_options::variables_map& get_config_vm();

        /**
         * \brief Get a configuration variable
         * \tparam T the type of the variable
         * \param name the name of the variable
         * \return the value of the variable
         */
        template<typename T>
        T const& get(std::string const& name)
        {
            return get_config_vm()[name].as<T>();
        }

        /**
         * \brief Set a configuration variable to a specific value
         * \tparam T type of the configuration variable
         * \param name name of the configuration variable
         * \param value the new value of the cofiguration variable
         */
        template<typename T>
        void set(std::string const& name, T const& value)
        {
            auto p = get_config_vm().find(name);
            if (p == get_config_vm().end())
            {
                get_config_vm().insert({name, boost::program_options::variable_value{value, false}});
            }
        }

        /**
         * \brief Check if a configration variable exists
         * \param name the name of the configuration variable to search for
         * \return if the variable exists or not
         * \retval true the variable exists
         * \retval false the variable doesn't exist
         */
        inline bool exists(std::string const& name)
        {
            return get_config_vm().count(name) > 0;
        }
    }
}

#endif //RETHINKMUD_CONFIG_H
