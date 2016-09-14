//
// Created by arrow on 9/13/16.
//

#ifndef RETHINKMUD_NETWORK_H
#define RETHINKMUD_NETWORK_H

#include <asio.hpp>

namespace rethinkmud
{
    namespace net
    {
        void init();

        void start();

        void stop();

        void clean();

        asio::io_service& get_io_service();
    }
}

#endif //RETHINKMUD_NETWORK_H
