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
        auto is_location(T&&)
        {
            return std::is_same<typename std::remove_reference<T>::type, location>::value;
        }
    }
}

#endif //RETHINKMUD_LOCATION_H
