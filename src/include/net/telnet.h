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

            protected:
                void input(std::vector<char> data) override;

            private:
                struct telnet_info_deleter
                {
                    void operator()(telnet_info*);
                };

                std::unique_ptr<telnet_info, telnet_info_deleter> info_;
            };
        }

        namespace servers
        {
            class telnet : public tcp_v4<connections::telnet>
            {
            public:
                explicit telnet(unsigned short port)
                    : tcp_v4<connections::telnet>{port}
                {}

                ~telnet()
                {}

            protected:

            private:
            };
        }
    }
}

#endif //RETHINKMUD_TELNET_H
