#include "autoconf.h"
#include <iostream>
#include "../rethinkdbxx/rethinkdb.h"
#include <experimental/filesystem>

namespace R = RethinkDB;

int main()
{
    std::cout << "Hello, World!" << std::endl;
    std::cout << "RethinkMUD version " << RETHINKMUD_VERSION << '\n';

    auto conn = R::connect();
    if (conn)
    {
        std::cout << "Connected\n" << std::flush;
        R::Cursor databases = R::db_list().run(*conn);
        for (R::Datum& db : databases)
        {
            std::cout << *db.get_string() << '\n';
        }
    }
    else
    {
        std::cerr << "Could not connect to server\n";
    }

    return 0;
}
