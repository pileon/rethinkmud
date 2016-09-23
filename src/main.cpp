#include "rethinkmud.h"
#include "net/network.h"

#include "rethinkdbxx.h"

#include <iostream>
#include <experimental/filesystem>

namespace R = RethinkDB;
using namespace rethinkmud;

namespace
{
    bool run_server = true;

    void init(int argc, char* argv[])
    {
        config::load(argc, argv);
        net::init();


        //struct sigaction sa = {};
        //sa.sa_handler = [](int) { std::cout << "SIGINT\n"; exit_program = true; };
        //sa.sa_flags   = SA_RESETHAND | SA_RESTART;
        //sigaction(SIGINT, &sa, nullptr);
    }

    void boot()
    {
        net::start();
    }

    void stop()
    {
        net::stop();
    }

    void clean()
    {
        net::clean();
    }
}

int main(int argc, char** argv)
{
    init(argc, argv);

    std::cout << config::get<std::string>("mud.name") << " version " << config::get<std::string>("mud.version") << " is starting up\n";
    std::cout << "Based on RethinkMUD version " << RETHINKMUD_VERSION << '\n';
    std::cout << "Administrated by " << config::get<std::string>("mud.admin.name") << " <" << config::get<std::string>("mud.admin.email") << ">\n";

    boot();

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

    while (run_server)
    {

    }

    stop();

    clean();

    return 0;
}

namespace rethinkmud
{
    void shutdown()
    {
        run_server = false;
    }
}
