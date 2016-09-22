#ifndef RETHINKMUD_RETHINKDBXX_H_H
#define RETHINKMUD_RETHINKDBXX_H_H

// This file is needed to (temporarily) disable some warnings that
// otherwise could spam the build output

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvla"
#pragma GCC diagnostic ignored "-Weffc++"

#include "../../rethinkdbxx/rethinkdb.h"

#pragma GCC diagnostic pop

#endif //RETHINKMUD_RETHINKDBXX_H_H
