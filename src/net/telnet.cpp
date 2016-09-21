#include "net/telnet.h"
#include "autoconf.h"

#define TELCMDS  // To get the array of Telnet command names
#define TELOPTS  // To get the array of Telnet option names
#include <arpa/telnet.h>

namespace
{
    std::string trim(std::string const& str)
    {
        // Find the first non-whitespace character
        auto first = std::find_if(std::cbegin(str), std::cend(str), [](char const& c)
        {
            return !std::isspace(c);
        });

        // Find the last non-whitespace character
        auto last = std::find_if(std::crbegin(str), std::crend(str), [](char const& c)
        {
            return !std::isspace(c);
        });

        size_t first_pos = first != std::cend(str) ? first - std::cbegin(str) : 0;
        size_t length = last != std::crend(str) ? (std::crend(str) - last) - first_pos : str.length();

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
                    i = handle_sb(i);
                    break;

                case AYT:
                    // TODO: Use the configured MUD name instead
                    write("RethinkMUD version " RETHINKMUD_VERSION " is alive and well.\r\n");
                    break;

                case IP:
                    std::clog << "Closing connection to " << socket().remote_endpoint() << " (Telnet IP)\n";
                    close();
                    return;

                case EC:
                    // Remove last character from input
                    input.erase(std::end(input) - 1);
                    break;

                case EL:
                    // Remove last "line" from input
                    erase_line(input);
                    break;

                    // TODO: AO: Clear the output queue?

                default:
                    if (TELCMD_OK(command))
                        std::clog << "Unhandled telnet command " << TELCMD(command) << '\n';
                    else
                        std::clog << "Unknown telnet command " << static_cast<unsigned>(command) << '\n';
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

            // TODO: Add input line to queue for command interpreter
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

        default:
            break;
    }
}

std::vector<char>::iterator rethinkmud::net::connections::telnet::handle_sb(std::vector<char>::iterator i)
{
    if (TELOPT_OK(*i))
    {
        std::clog << "Unhandled telnet SB " << TELOPT(*i) << '\n';
    }
    else
    {
        std::clog << "Unknown SB " << *i << '\n';
        return skip_sb(i);
    }

    // TODO: Handle some SB?
    return skip_sb(i);
}

std::vector<char>::iterator rethinkmud::net::connections::telnet::skip_sb(std::vector<char>::iterator i)
{
    while (static_cast<uint8_t>(*i) != IAC && static_cast<uint8_t>(*(i + 1)) != SE)
    {
        ++i;
    }

    return i + 1;
}

void rethinkmud::net::connections::telnet::erase_line(std::string& input)
{
    std::string::const_reverse_iterator i;
    for (i = std::crbegin(input); i != std::crend(input); ++i)
    {
        // Check for \r\n
        if (*i == '\n' && (i + 1) != std::crend(input) && *(i + 1) == '\r')
        {
            break;
        }

        // For safety, check for \n\r too
        if (*i == '\r' && (i + 1) != std::crend(input) && *(i + 1) == '\n')
        {
            break;
        }
    }

    if (i == std::crend(input))
    {
        // No newline found, erase all
        input.erase();
    }
    else
    {
        // Remove up until last newline
        input = input.substr(0, std::crend(input) - i);
    }
}
