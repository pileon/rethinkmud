#ifndef RETHINKMUD_THING_H
#define RETHINKMUD_THING_H

#include <tuple>
#include <string>
#include <unordered_map>

#if defined(HAVE_HEADER_ANY)
# include <any>
#elif defined(HAVE_HEADER_EXPERIMENTAL_ANY)
# include <experimental/any>
#elif defined(HAVE_HEADER_BOOST_ANY_HPP)
# include <boost/any.hpp>
namespace std
{
    using any = boost::any;
    using bad_any_cast = boost::bad_any_cast;
    using boost::swap;
    using boost::any_cast;
}
#else
# error "No any header available"
#endif

#if defined(HAVE_HEADER_EXPERIMENTAL_ANY) || defined(HAVE_HEADER_EXPERIMENTAL_OPTIONAL)
namespace std
{
    using namespace experimental;
}
#endif

namespace rethinkmud
{
    namespace db
    {
        /**
         * \brief A thing in the MUD world
         * \tparam traitsT Traits class for the thing
         *
         * Things have attributes. Some attributes are simple, like a string
         * describing the thing, or it can be complex like a container of
         * other things. All attributes have a name.
         */
        template<typename traitsT>
        class thing
        {
        public:
            thing()
                : attributes_{}
            {
                add_thing_attributes();
            }

            virtual ~thing()
            {}

            std::any& get(std::string const& name)
            {
                return attributes_[name];
            }

            std::any& operator[](std::string const& name)
            {
                return get(name);
            }

            //std::any const& operator[](std::string const& name) const
            //{
            //    return const_cast<std::any const&>(attributes_[name]);
            //}

        private:
            std::unordered_map<std::string, std::any> attributes_;

            void add_thing_attributes()
            {
                // All things have a location
                attributes_["location"] = static_cast<thing*>(nullptr);
            }
        };
    }
}

#endif //RETHINKMUD_THING_H
