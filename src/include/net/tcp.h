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
        namespace connections
        {
            class tcp : public ip<asio::ip::tcp>
            {
            public:
                using socket_type = typename ip<asio::ip::tcp>::socket_type;

                tcp(socket_type socket)
                    : ip<asio::ip::tcp>{std::move(socket)}
                {}

                virtual ~tcp()
                {}
            };
        }

        namespace servers
        {
            template<typename ConnectionT = connections::tcp>
            using tcp_v4 = ip_v4<asio::ip::tcp, ConnectionT>;

            template<typename ConnectionT = connections::tcp>
            using tcp_v6 = ip_v6<asio::ip::tcp, ConnectionT>;
        }
    }
}

#endif //RETHINKMUD_TCP_H
