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
#include <vector>

namespace rethinkmud
{
    namespace net
    {
        namespace connections
        {
            /**
             * \brief Base class for IP-based connections
             *
             * \tparam AddressFamilyT The ASIO address family structure type
             */
            template<typename AddressFamilyT>
            class ip : public basic_connection,
            public std::enable_shared_from_this<ip<AddressFamilyT>>
            {
            public:
                using socket_type = typename AddressFamilyT::socket;

                /**
                 * \brief Start the asynchronous receive process
                 */
                void run()
                {
                    start();
                    do_read();
                }

                using basic_connection::write;

                void write(std::vector<char> const& data) override
                {
                    socket_.send(asio::buffer(data));
                }

            protected:
                ip(socket_type socket)
                        : basic_connection{},
                          std::enable_shared_from_this<ip>{},
                          socket_{std::move(socket)}
                {

                }

                /**
                 * \brief Return the underlying socket
                 *
                 * \return The socket
                 */
                socket_type socket() const
                {
                    return socket_;
                }

                /**
                 * \brief Connection has started up
                 */
                void start() override
                {
                    std::clog << "New connection from " << socket_.remote_endpoint() << '\n';
                }

                /**
                 * \brief The connection is ending
                 *
                 * \param ec Reason for ending the connection
                 */
                void end(std::error_code const& ec) const override
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
                                    this->input(std::vector<char>(data_.data(), data_.data() + size));
                                    do_read();
                                }
                                else
                                {
                                    end(ec);
                                }
                            });
                }
            };
        }

        namespace servers
        {
            /**
             * \brief Generic parent class for TCP or UDP servers
             *
             * \tparam AddressFamilyT The TCP or UDP base class
             * \tparam version_func Function to get an IP version
             * \tparam ConnectionT Type of the connection object to create
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

                    start();
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
                            std::make_shared<ConnectionT>(std::move(socket_))->run();
                        }
                        else
                        {
                            // TODO: Check what kind of error this is, if we can continue or need to end
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
