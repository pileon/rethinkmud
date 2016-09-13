//
// Created by arrow on 9/13/16.
//

#ifndef RETHINKMUD_CONNECTION_H
#define RETHINKMUD_CONNECTION_H

namespace rethinkmud
{
    namespace net
    {
        namespace connections
        {
            /**
             * \brief Abstract base class for all servers
             */
            class basic_connection
            {
            public:
                virtual ~basic_connection()
                {}

            protected:
                basic_connection()
                {}

            private:
            };
        }
    }
}

#endif //RETHINKMUD_CONNECTION_H
