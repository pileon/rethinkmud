//
// Created by arrow on 9/13/16.
//

#ifndef RETHINKMUD_SERVER_H
#define RETHINKMUD_SERVER_H

namespace rethinkmud
{
    namespace net
    {
        namespace servers
        {
            /**
             * \brief Abstract base class for all servers
             */
            class basic_server
            {
            public:
                virtual ~basic_server()
                {}

            protected:
                basic_server()
                {}

                virtual void start()
                {
                }

            private:
            };
        }
    }
}

#endif //RETHINKMUD_SERVER_H
