//
// Created by arrow on 9/13/16.
//

#ifndef RETHINKMUD_CONNECTION_H
#define RETHINKMUD_CONNECTION_H

#include <iostream>
#include <vector>

namespace rethinkmud
{
    namespace net
    {
        namespace connections
        {
            /**
             * \brief Abstract base class for all servers
             */
            class basic_connection
            {
            public:
                virtual ~basic_connection()
                {}

                virtual void write(std::string const&string)
                {
                    write(std::vector<char>(std::begin(string), std::end(string)));
                }
                virtual void write(uint8_t const* data, size_t const length)
                {
                    write(std::vector<char>(data, data + length));
                }
                virtual void write(std::vector<char> const&) = 0;

            protected:
                basic_connection()
                {}

                /**
                 * \brief Connection has started up
                 */
                virtual void start()
                {
                }

                /**
                 * \brief The connection is ending
                 *
                 * \param ec Reason for ending the connection
                 */
                virtual void end(std::error_code const& ec [[maybe_unused]]) const
                {
                }

                /**
                 * \brief Input have been received
                 *
                 * \param data A vector of the received data
                 */
                virtual void input(std::vector<char> data)
                {
                    std::clog << "Received " << data.size() << " bytes: \"" << std::string(data.data(), data.size()) << "\"\n";
                }

            private:
            };
        }
    }
}

#endif //RETHINKMUD_CONNECTION_H
