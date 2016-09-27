#ifndef RETHINKMUD_CHARACTER_H
#define RETHINKMUD_CHARACTER_H

#include "thing.h"

namespace rethinkmud
{
    namespace db
    {
        class character : public thing<character>
        {

        };

        template<typename T>
        auto is_character(T&&)
        {
            return std::is_same<typename std::remove_reference<T>::type, character>::value;
        }
    }
}

#endif //RETHINKMUD_CHARACTER_H
