#ifndef RETHINKMUD_CONFIG_H
#define RETHINKMUD_CONFIG_H

#include <string>

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
         * \brief Get a configuration variable
         * \tparam T the type of the variable
         * \param name the name of the variable
         * \return the value of the variable
         */
        template<typename T>
        T get(std::string name);
    }
}

#endif //RETHINKMUD_CONFIG_H
