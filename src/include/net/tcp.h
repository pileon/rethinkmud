//
// Created by arrow on 9/13/16.
//

#ifndef RETHINKMUD_TCP_H
#define RETHINKMUD_TCP_H

#include "server.h"

namespace rethinkmud
{
    namespace net
    {
        class tcp_server : public server
        {
        public:
            tcp_server() {}
            virtual ~tcp_server() {}

        protected:

        private:
        };
    }
}

#endif //RETHINKMUD_TCP_H
