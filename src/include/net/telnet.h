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
        namespace servers
        {
            class telnet : public tcp_v4
            {
            public:
                explicit telnet(unsigned short port)
                    : tcp_v4{port}
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
