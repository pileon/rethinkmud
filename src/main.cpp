#include "autoconf.h"
#include "config.h"

#include "../rethinkdbxx/rethinkdb.h"

#include <iostream>
#include <experimental/filesystem>

namespace R = RethinkDB;

int main(int argc, char** argv)
{
    using namespace rethinkmud;
    config::load(argc, argv);

    std::cout << "RethinkMUD version " << RETHINKMUD_VERSION << '\n';

    try
    {
        auto conn = R::connect();

        std::cout << "Connected\n" << std::flush;
        auto databases = R::db_list().run(*conn);
        for (auto const& db : databases)
        {
            std::cout << *db.get_string() << '\n';
        }
    }
    catch (R::Error& e)
    {
        std::cerr << "Could not connect to server: " << e.message << '\n';
    }

    return 0;
}
