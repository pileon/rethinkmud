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

                // TODO: Functions for writing data to the connection

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
