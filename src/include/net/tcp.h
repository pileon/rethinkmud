//
// Created by arrow on 9/13/16.
//

#ifndef RETHINKMUD_TCP_H
#define RETHINKMUD_TCP_H

#include "ip.h"
#include "network.h"

namespace rethinkmud
{
    namespace net
    {
        namespace servers
        {
            using tcp_v4 = ip_v4<asio::ip::tcp>;
            using tcp_v6 = ip_v6<asio::ip::tcp>;
        }
    }
}

#endif //RETHINKMUD_TCP_H
