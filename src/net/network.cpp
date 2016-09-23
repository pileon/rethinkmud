#include "net/network.h"
#include "net/server.h"
#include "net/telnet.h"
#include "config.h"

#include <thread>

using namespace rethinkmud::net;

namespace
{
    std::vector<std::unique_ptr<servers::basic_server>> all_servers;
    asio::io_service io_service;
    std::thread io_service_thread;
}

void rethinkmud::net::init()
{
}

void rethinkmud::net::start()
{
    io_service_thread = std::thread{[]() {
        while (!io_service.stopped())
            io_service.run();
    }};

    all_servers.emplace_back(std::make_unique<servers::telnet>(config::get<unsigned short>("net.telnet.port")));
}

void rethinkmud::net::stop()
{
    io_service.stop();
    io_service_thread.join();
}

void rethinkmud::net::clean()
{
}

asio::io_service& rethinkmud::net::get_io_service()
{
    return io_service;
}
