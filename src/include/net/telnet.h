//
// Created by arrow on 9/13/16.
//

#ifndef RETHINKMUD_TELNET_H
#define RETHINKMUD_TELNET_H

#include "tcp.h"

namespace rethinkmud
{
    namespace net
    {
        namespace connections
        {
            class telnet : public tcp
            {
                struct telnet_info;

            public:
                using socket_type = tcp::socket_type;

                telnet(socket_type socket)
                    : tcp{std::move(socket)}
                {}

                ~telnet()
                {}

                void start() override;

                void echo_on();
                void echo_off();

            protected:
                void input(std::vector<char> data) override;

            private:
                struct telnet_info_deleter
                {
                    void operator()(telnet_info*);
                };

                std::unique_ptr<telnet_info, telnet_info_deleter> info_;

                std::string buffer_;  // Buffer from last input operation

                void send_option(uint8_t command, uint8_t option);
                void send_do(uint8_t option);
                void send_dont(uint8_t option);
                void send_will(uint8_t option);
                void send_wont(uint8_t option);

                void handle_option(uint8_t command, uint8_t option);
                std::vector<char>::iterator handle_sb(std::vector<char>::iterator);
                std::vector<char>::iterator skip_sb(std::vector<char>::iterator);
                void erase_line(std::string& input);
            };
        }

        namespace servers
        {
            class telnet : public tcp_v4<connections::telnet>
            {
            public:
                explicit telnet(unsigned short port)
                    : tcp_v4<connections::telnet>{port}
                {
                    log::info("net") << "Telnet server listening on port " << port;
                }

                ~telnet()
                {}

            protected:

            private:
            };
        }
    }
}

#endif //RETHINKMUD_TELNET_H
