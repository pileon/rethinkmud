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
            class telnet : public tcp
            {
            public:
                explicit telnet(unsigned short port)
                    : tcp{port}
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
