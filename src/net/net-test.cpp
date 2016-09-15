// This simple program initializes the network components, and then waits
// for the user to interrupt the program with CTRL-C

#include <iostream>
#include "net/network.h"

namespace n = rethinkmud::net;

namespace
{
    bool exit_program = false;
}

int main()
{
    char x = 0xff;
    std::cout << "static_cast<int>(static_cast<unsigned char>(x)) = " << static_cast<int>(static_cast<unsigned char>(x)) << '\n';

    std::cout << "1 '\u2126'\n";
    std::cout << "1 '\u03a9'\n";
    std::cout << "2 '\u0061\u0300'\n";
    std::cout << "2 '\u00e0'\n";

    struct sigaction sa = {};
    sa.sa_handler = [](int) { std::cout << "SIGINT\n"; exit_program = true; };
    sa.sa_flags   = SA_RESETHAND | SA_RESTART;
    sigaction(SIGINT, &sa, nullptr);

    n::init();
    n::start();

    while (!exit_program)
    {
        pause();
    }

    n::stop();
    n::clean();
}
