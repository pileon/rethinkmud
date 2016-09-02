#include "autoconf.h"
#include <iostream>
#include "../rethinkdbxx/rethinkdb.h"

namespace R = RethinkDB;

int main()
{
    std::cout << "Hello, World!" << std::endl;
    std::cout << "RethinkMUD version " << RETHINKMUD_VERSION << '\n';

    auto conn = R::connect();
    if (conn)
    {
        std::cout << "Connected\n";
        auto databases = R::db_list().run(*conn);
    }
    else
    {
        std::cerr << "Could not connect to server\n";
    }

    return 0;
}
