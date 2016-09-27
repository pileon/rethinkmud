#ifndef RETHINKMUD_THING_H
#define RETHINKMUD_THING_H

#include <tuple>
#include <string>
#include <unordered_map>

#if defined(HAVE_HEADER_ANY)
# include <any>
#elif defined(HAVE_HEADER_EXPERIMENTAL_ANY)
# include <experimental/any>
namespace std { using any = experimental::any; }
#elif defined(HAVE_HEADER_BOOST_ANY_HPP)
# include <boost/any.hpp>
namespace std { using any = boost::any; }
#else
# error "No any header available"
#endif

namespace rethinkmud
{
    namespace db
    {
        /**
         * \brief A thing in the MUD world
         */
        class thing
        {
        public:
            thing()
                : attributes_{}
            {}

            virtual ~thing()
            {}

        private:
            std::unordered_map<std::string, std::any> attributes_;
        };
    }
}

#endif //RETHINKMUD_THING_H
