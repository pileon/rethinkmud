//
// Created by arrow on 9/13/16.
//

#include <iostream>
#include "net/network.h"

namespace n = rethinkmud::net;

namespace
{
    bool exit_program = false;
}

int main()
{
    struct sigaction sa = {};
    sa.sa_handler = [](int) { std::cout << "SIGINT\n"; exit_program = true; };
    sa.sa_flags   = SA_RESETHAND | SA_RESTART;
    sigaction(SIGINT, &sa, nullptr);

    n::init();
    n::start();

    while (!exit_program)
    {

    }

    n::stop();
    n::clean();
}
