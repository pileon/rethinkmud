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

    void signal_setup()
    {
        struct sigaction sa = {};
        sa.sa_handler = [](int sig)
        {
            std::cout << std::flush;
            std::clog << std::flush;
            psignal(sig, "Received termination signal");
            run_server = false;
        };
        sa.sa_flags   = SA_RESTART;
        sigaction(SIGINT, &sa, nullptr);
        sigaction(SIGTERM, &sa, nullptr);
        sigaction(SIGHUP, &sa, nullptr);

        // We want to get an error when writing to a closed network connection, not a signal
        sa.sa_handler = SIG_IGN;
        sigaction(SIGPIPE, &sa, nullptr);
    }

    void init(int argc, char* argv[])
    {
        config::load(argc, argv);
        log::init();
        net::init();

        signal_setup();
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
        log::clean();
    }
}

int main(int argc, char** argv)
{
    init(argc, argv);

    log::info() << config::get<std::string>("mud.name") << " version " << config::get<std::string>("mud.version") << " is starting up";
    log::info() << "Based on RethinkMUD version " << RETHINKMUD_VERSION;
    log::info() << "Administrated by " << config::get<std::string>("mud.admin.name") << " <" << config::get<std::string>("mud.admin.email") << '>';
    log::debug() << "Server running pid " << getpid();

    boot();

    //try
    //{
    //    auto conn = R::connect();
    //
    //    std::cout << "Connected\n" << std::flush;
    //    auto databases = R::db_list().run(*conn);
    //    for (auto const& db : databases)
    //    {
    //        std::cout << *db.get_string() << '\n';
    //    }
    //}
    //catch (R::Error& e)
    //{
    //    std::cerr << "Could not connect to server: " << e.message << '\n';
    //}
    //
    //while (run_server)
    //{
    //    pause();
    //}

    log::info() << "Shuting down server...";

    stop();

    clean();

    log::info() << "All done";
    return 0;
}

namespace rethinkmud
{
    void shutdown()
    {
        run_server = false;
    }
}
