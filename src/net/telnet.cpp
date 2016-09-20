#include "net/telnet.h"

#include <arpa/telnet.h>

namespace
{
    std::string trim(std::string const& str)
    {
        // Find the first non-whitespace character
        auto first = std::find_if(std::begin(str), std::end(str), [](char const& c)
        {
            return !std::isspace(c);
        });

        // Find the last non-whitespace character
        auto last = std::find_if(std::rbegin(str), std::rend(str), [](char const& c)
        {
            return !std::isspace(c);
        });

        size_t first_pos = first != std::end(str) ? first - std::begin(str) : 0;
        size_t length = last != std::rend(str) ? (std::rend(str) - last) - first_pos : str.length();

        return str.substr(first_pos, length);
    }
}

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

    if (!buffer_.empty())
    {
        input = buffer_;
        buffer_ = "";  // Clear the saved buffer from last call
    }

    for (auto i = std::begin(data); i != std::end(data); ++i)
    {
        if (static_cast<uint8_t>(*i) == IAC)
        {
            uint8_t command = static_cast<uint8_t>(*++i);

            // TODO: Handle all this
            switch (command)
            {
                case DO:
                case DONT:
                case WILL:
                case WONT:
                    handle_option(command, *++i);
                    break;

                case SB:
                    break;

                case AYT:
                    break;

                default:
                    break;
            }
        }
        else
            input += *i;
    }

    if (input.empty())
        return;

    std::istringstream iss{input};
    std::string line;

    while (std::getline(iss, line))
    {
        if (iss.eof())
        {
            // Not a complete line at the end of the buffer, save the data for the next call to this function
            buffer_ = line;
        }
        else
        {
            // Trim leading and trailing white-space
            line = trim(line);

            if (line == "echo off")
                echo_off();
            else if (line == "echo on")
                echo_on();
            else
                write("You wrote: " + line + "\r\n");

            // TODO: Add input line to queue
        }
    }
}

void rethinkmud::net::connections::telnet::send_option(uint8_t command, uint8_t option)
{
    uint8_t const data[] = {
        IAC,
        command,
        option
    };
    write(data, sizeof(data));
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
    send_wont(TELOPT_ECHO);
    send_do(TELOPT_ECHO);
}

void rethinkmud::net::connections::telnet::echo_off()
{
    send_will(TELOPT_ECHO);
    send_dont(TELOPT_ECHO);
}

void rethinkmud::net::connections::telnet::handle_option(uint8_t command, uint8_t option)
{
    // TODO: Handle all this
    switch (command)
    {
        case DO:
            if (info_->sent_will[option])
            {
            }
            else if (info_->sent_wont[option])
            {
            }
            else
            {
                send_wont(option);
            }
            break;

        case DONT:
            if (info_->sent_will[option])
            {
            }
            else if (info_->sent_wont[option])
            {
            }
            else
            {
                send_wont(option);
            }
            break;

        case WILL:
            if (info_->sent_do[option])
            {
            }
            else if (info_->sent_dont[option])
            {
            }
            else
            {
                send_dont(option);
            }
            break;
        case WONT:
            if (info_->sent_do[option])
            {
            }
            else if (info_->sent_dont[option])
            {
            }
            else
            {
                send_dont(option);
            }
            break;
    }
}
