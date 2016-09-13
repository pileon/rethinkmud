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
            public:
                using tcp::tcp;
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
