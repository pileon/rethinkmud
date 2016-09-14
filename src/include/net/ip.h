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
#include <iostream>

namespace rethinkmud
{
    namespace net
    {
        namespace connections
        {
            template<typename AddressFamilyT>
            class ip : public std::enable_shared_from_this<ip<AddressFamilyT>>,
                       public basic_connection
            {
            public:
                using socket_type = typename AddressFamilyT::socket;

                ip(socket_type socket)
                    : std::enable_shared_from_this<ip>{},
                      basic_connection{},
                      socket_{std::move(socket)}
                {

                }

                void start()
                {
                    std::clog << "New connection from " << socket_.remote_endpoint() << '\n';
                    do_read();
                }

            private:
                enum { DATA_SIZE = 1024 };

                socket_type socket_;
                std::array<char, DATA_SIZE> data_;

                void do_read()
                {
                    auto self = this->shared_from_this();
                    socket_.async_read_some(
                            asio::buffer(data_),
                            [this, self](std::error_code ec, std::size_t size)
                            {
                                if (!ec)
                                {
                                    std::clog << "Received " << size << " bytes: \"" << std::string(data_.data(), size) << "\"\n";
                                    do_read();
                                }
                                else
                                {
                                    if (ec == asio::error::eof)
                                    {
                                        std::clog << "Connection to " << socket_.remote_endpoint() << " Closed\n";
                                    }
                                    else
                                    {
                                        std::clog << "Error: " << ec << " (" << ec.message() << ")\n";
                                    }
                                }
                            });
                }
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
                    typename AddressFamilyT::acceptor::reuse_address option(true);
                    acceptor_.set_option(option);

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
