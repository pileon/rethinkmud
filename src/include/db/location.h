#ifndef RETHINKMUD_LOCATION_H
#define RETHINKMUD_LOCATION_H

#include "thing.h"

namespace rethinkmud
{
    namespace db
    {
        class location : public thing<location>
        {

        };

        template<typename T>
        bool is_location(T&&)
        {
            return std::is_same<T, location>::value;
        }
    }
}

#endif //RETHINKMUD_LOCATION_H
