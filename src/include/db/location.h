#ifndef RETHINKMUD_LOCATION_H
#define RETHINKMUD_LOCATION_H

#include "thing.h"
#include "character.h"

namespace rethinkmud
{
    namespace db
    {
        class location : public thing<location>
        {
        public:
            template<typename T>
            void add(T&& thing)
            {
                if (is_character(thing))
                {
                    if (get("characters"))
                    {
                        auto& characters = std::any_cast<std::vector<character*>>(*get("characters"));
                        characters.push_back(&thing);
                    }
                    else
                    {
                        *get("characters") = std::vector<character*>{&thing};
                    }
                }

                thing.get("location") = this;
            }
        };

        template<typename T>
        auto is_location(T&&)
        {
            return std::is_same<typename std::remove_reference<T>::type, location>::value;
        }
    }
}

#endif //RETHINKMUD_LOCATION_H
