//
// Created by arrow on 9/13/16.
//

#include "net/network.h"

namespace n = rethinkmud::net;

int main()
{
    n::init();
    n::start();
    n::stop();
    n::clean();
}
