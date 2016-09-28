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
            location()
                : thing{}
            {
                add_location_attributes();
            }

            template<typename T>
            void to(T&& something)
            {
                auto current_location = std::any_cast<thing*>(something["location"]);
                if (current_location == this)
                {
                    return;
                }

                if (is_character(something))
                {
                    // Remove thing from current location
                    if (current_location != nullptr)
                    {
                        std::any_cast<std::vector<character *>>(current_location->get("characters")).erase(something);
                    }

                    // Add thing to this location
                    std::any_cast<std::vector<character*>>(get("characters")).push_back(&something);
                }

                something.get("location") = this;
            }

        private:

            void add_location_attributes()
            {
                get("characters") = std::vector<character*>{};
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
