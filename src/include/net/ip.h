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
                using pointer_type = std::shared_ptr<ip>;
                using socket_type  = typename AddressFamilyT::socket;

                static pointer_type create()
                {
                    return std::make_shared<ip>();
                }

                ip()
                    : socket_{get_io_service()}
                {
                }

                socket_type& socket()
                {
                    return socket_;
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
            template<typename AddressFamilyT>
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
                          acceptor_v4_{get_io_service(), typename AddressFamilyT::endpoint{AddressFamilyT::v4(), port_}},
                          acceptor_v6_{get_io_service(), typename AddressFamilyT::endpoint{AddressFamilyT::v6(), port_}}
                {
                    start_accept_v4();
                    start_accept_v6();
                }

            private:
                unsigned short port_;

                typename AddressFamilyT::acceptor acceptor_v4_;
                typename AddressFamilyT::acceptor acceptor_v6_;

                void start_accept_v4()
                {
                    auto connection = connection_type::create();
                    acceptor_v4_.async_accept(connection->socket(),
                                              std::bind(&ip::handle_accept, this,
                                                        boost::asio::placeholders::error));
                }

                void start_accept_v6()
                {

                }

                void handle_accept(typename connection_type::pointer_type connection [[maybe_unused]],
                                   const boost::system::error_code& error [[maybe_unused]])
                {
                    //restart_function();
                }
            };
        }
    }
}

#endif //RETHINKMUD_IP_H
