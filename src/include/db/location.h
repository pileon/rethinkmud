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
            void to(T&& thing)
            {
                auto& current_location = thing["location"];
                if (current_location == this)
                {
                    return;
                }

                if (is_character(thing))
                {
                    // Remove thing from current location
                    std::any_cast<std::vector<character*>>(current_location["characters"]).erase(thing);

                    // Add thing to this location
                    std::any_cast<std::vector<character*>>((*this)["characters"]).push_back(&thing);
                }

                thing.get("location") = this;
            }

        private:

            void add_location_attributes()
            {
                (*this)["characters"] = std::vector<character*>{};
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
