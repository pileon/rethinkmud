#include "net/telnet.h"

#include <arpa/telnet.h>

static constexpr std::size_t telnet_option_count = 256;

struct rethinkmud::net::connections::telnet::telnet_info
{
    // What we do, and don't do
    bool options[telnet_option_count] = { false };

    // Options we have sent and are waiting for reply on
    bool sent_will[telnet_option_count];
    bool sent_wont[telnet_option_count];
    bool sent_do[telnet_option_count];
    bool sent_dont[telnet_option_count];
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
    // Parse the input for telnet command sequence
    // Copy the non-telnet data to a new container
    // For now we assume that all sequences are complete

    std::string input;

    for (auto i = std::begin(data); i != std::end(data); ++i)
    {
        if (static_cast<unsigned char>(*i) == IAC)
        {
            // TODO: Handle the telnet stuff
        }
        else
            input += *i;
    }

    // TODO: Pass the input to the command interpreter
}
