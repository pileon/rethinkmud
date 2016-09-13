#include "net/network.h"
#include "net/server.h"
#include "net/telnet.h"

#include <memory>
#include <vector>
#include <thread>

using namespace rethinkmud::net;

namespace
{
    std::vector<std::unique_ptr<servers::basic_server>> all_servers;
    boost::asio::io_service io_service;
    std::thread io_service_thread;
}

void rethinkmud::net::init()
{
    all_servers.emplace_back(new servers::telnet{4000});
}

void rethinkmud::net::start()
{
    io_service_thread = std::thread{[]() {
        while (!io_service.stopped())
            io_service.run();
    }};
}

void rethinkmud::net::stop()
{
    io_service.stop();
    io_service_thread.join();
}

void rethinkmud::net::clean()
{
}

boost::asio::io_service& rethinkmud::net::get_io_service()
{
    return io_service;
}
