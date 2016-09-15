#include "net/telnet.h"

#include <arpa/telnet.h>

struct rethinkmud::net::connections::telnet::telnet_info
{
    int x;
};

void rethinkmud::net::connections::telnet::telnet_info_deleter::operator()(telnet_info* info)
{
    delete info;
}

void rethinkmud::net::connections::telnet::start()
{
    std::clog << "Starting telnet connection\n";
    info_.reset(new telnet_info);

    tcp::start();
}

void rethinkmud::net::connections::telnet::input(std::vector<char> data)
{
    // TODO: Parse the input for telnet command sequence
    // TODO: Extract (remove) the command sequences as we process the input
    // TODO: For now we assume that all sequences are complete

    // TODO: After parsing and removing the telnet sequences,
    // TODO: the rest of the data is passed as a string to the
    // TODO: command interpreter
}
