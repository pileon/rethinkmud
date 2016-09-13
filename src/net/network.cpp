#include "net/network.h"
#include "net/server.h"
#include "net/telnet.h"

#include <memory>
#include <vector>
#include <thread>

#include <boost/asio.hpp>
#include <iostream>

namespace
{
    std::vector<std::unique_ptr<rethinkmud::net::server>> servers;
    boost::asio::io_service io_service;
    std::thread io_service_thread;
}

void rethinkmud::net::init()
{
    servers.emplace_back(new telnet_server);

    // TODO: Initialization needed
}

void rethinkmud::net::start()
{
    std::cout << "io_service.stopped() == " << std::boolalpha << io_service.stopped() << '\n';

    io_service_thread = std::thread{[&]() {
        while (!io_service.stopped())
            io_service.run();
    }};

    // TODO: Start servers and threads
}

void rethinkmud::net::stop()
{
    io_service.stop();
    io_service_thread.join();

    // TODO: Stop servers and threads
}

void rethinkmud::net::clean()
{
    // TODO: Clean up after us
}
