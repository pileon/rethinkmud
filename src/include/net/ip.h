//
// Created by arrow on 9/13/16.
//

#ifndef RETHINKMUD_IP_H
#define RETHINKMUD_IP_H

#include "server.h"
#include "connection.h"
#include "network.h"

#include <memory>
#include <functional>

namespace rethinkmud
{
    namespace net
    {
        namespace connections
        {
            template<typename AddressFamilyT>
            class ip : public basic_connection,
                       public std::enable_shared_from_this<ip<AddressFamilyT>>
            {
            public:
                using socket_type = typename AddressFamilyT::socket;

                ip(socket_type socket)
                    : basic_connection{},
                      socket_{std::move(socket)}
                {

                }

                void start()
                {
                    // TODO: Start asynchronous reading from the socket
                    // TODO: Handle input some nice way
                }

            private:
                socket_type socket_;
            };
        }

        namespace servers
        {
            /**
             * \brief Generic parent class for TCP or UDP servers
             * \tparam AddressFamilyT The TCP or UDP base class
             */
            template<typename AddressFamilyT, AddressFamilyT (*version_func)(), typename ConnectionT>
            class ip : public basic_server
            {
            public:
                using connection_type = connections::ip<AddressFamilyT>;

                virtual ~ip()
                {}

            protected:
                explicit ip(unsigned short port)
                        : basic_server{},
                          port_{port},
                          acceptor_{get_io_service(), typename AddressFamilyT::endpoint{version_func(), port_}},
                          socket_{get_io_service()}
                {
                    do_accept();
                }

            private:
                unsigned short port_;

                typename AddressFamilyT::acceptor acceptor_;
                typename AddressFamilyT::socket   socket_;

                void do_accept()
                {
                    acceptor_.async_accept(socket_, [this](std::error_code ec)
                    {
                        if (!ec)
                        {
                            std::make_shared<ConnectionT>(std::move(socket_))->start();
                        }

                        do_accept();
                    });
                }
            };

            template<typename AddressFamilyT, typename ConnectionT>
            using ip_v4 = ip<AddressFamilyT, AddressFamilyT::v4, ConnectionT>;

            template<typename AddressFamilyT, typename ConnectionT>
            using ip_v6 = ip<AddressFamilyT, AddressFamilyT::v6, ConnectionT>;
        }
    }
}

#endif //RETHINKMUD_IP_H
