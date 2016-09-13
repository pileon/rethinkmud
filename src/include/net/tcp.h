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
            class tcp : public ip<boost::asio::ip::tcp>
            {
            public:
                explicit tcp(unsigned short port)
                    : ip{port}
                {}

                virtual ~tcp()
                {}
            };
        }
    }
}

#endif //RETHINKMUD_TCP_H
