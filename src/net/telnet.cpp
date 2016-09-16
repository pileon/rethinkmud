#include "net/telnet.h"

#include <arpa/telnet.h>

static constexpr std::size_t telnet_option_count = 256;

struct rethinkmud::net::connections::telnet::telnet_info
{
    // What we do, and don't do
    bool options[telnet_option_count] = { false };

    // Options we have sent and are waiting for reply on
    bool sent_will[telnet_option_count] = { false };
    bool sent_wont[telnet_option_count] = { false };
    bool sent_do[telnet_option_count] = { false };
    bool sent_dont[telnet_option_count] = { false };
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

void rethinkmud::net::connections::telnet::send_option(uint8_t command, uint8_t option)
{
    uint8_t const data[] = {
        IAC,
        command,
        option
    };

    // TODO: Send the data
}

void rethinkmud::net::connections::telnet::send_do(uint8_t option)
{
    if (!info_->sent_do[option])
    {
        send_option(DO, option);
        info_->sent_do[option] = true;
    }
}

void rethinkmud::net::connections::telnet::send_dont(uint8_t option)
{
    if (!info_->sent_dont[option])
    {
        send_option(DONT, option);
        info_->sent_dont[option] = true;
    }
}

void rethinkmud::net::connections::telnet::send_will(uint8_t option)
{
    if (!info_->sent_will[option])
    {
        send_option(WILL, option);
        info_->sent_will[option] = true;
    }
}

void rethinkmud::net::connections::telnet::send_wont(uint8_t option)
{
    if (!info_->sent_wont[option])
    {
        send_option(WONT, option);
        info_->sent_wont[option] = true;
    }
}

void rethinkmud::net::connections::telnet::echo_on()
{
    send_wont(ECHO);
    send_do(ECHO);
}

void rethinkmud::net::connections::telnet::echo_off()
{
    send_will(ECHO);
    send_dont(ECHO);
}
