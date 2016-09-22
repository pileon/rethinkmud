#include "autoconf.h"
#include "config.h"

#include "rethinkdbxx.h"

#include <iostream>
#include <experimental/filesystem>

namespace R = RethinkDB;

int main(int argc, char** argv)
{
    using namespace rethinkmud;
    config::load(argc, argv);

    std::cout << config::get<std::string>("mud.name") << " version " << config::get<std::string>("mud.version") << " is starting up\n";
    std::cout << "Based on RethinkMUD version " << RETHINKMUD_VERSION << '\n';
    std::cout << "Administrated by " << config::get<std::string>("mud.admin.name") << " <" << config::get<std::string>("mud.admin.email") << ">\n";

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
