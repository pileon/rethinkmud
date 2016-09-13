//
// Created by arrow on 9/13/16.
//

#ifndef RETHINKMUD_SERVER_H
#define RETHINKMUD_SERVER_H

namespace rethinkmud
{
    namespace net
    {
        /**
         * \brief Abstract base class for all servers
         */
        class server
        {
        public:
            virtual ~server() {}

        protected:
            server() {}

        private:
        };
    }
}

#endif //RETHINKMUD_SERVER_H
