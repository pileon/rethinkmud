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
        class telnet_server : public tcp_server
        {
        public:
            telnet_server() {}
            ~telnet_server() {}

        protected:

        private:
        };
    }
}

#endif //RETHINKMUD_TELNET_H
