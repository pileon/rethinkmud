#ifndef RETHINKMUD_LOG_H
#define RETHINKMUD_LOG_H

#include <sstream>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/logger.hpp>

namespace rethinkmud
{
    namespace log
    {
        void init();
        void clean();

        boost::log::sources::logger_mt& get_logger();

        class logger
        {
        public:
            logger(boost::log::trivial::severity_level const& severity)
                : oss_{},
                  severity_{severity}
            {}

            logger(logger&& l)
                : oss_{std::move(l.oss_)},
                  severity_{l.severity_}
            {}

            ~logger()
            {
                BOOST_LOG(get_logger()) << oss_.str();
            }

            template<typename T>
            logger& operator<<(T const& x)
            {
                oss_ << x;
                return *this;
            }

        private:
            std::ostringstream oss_;
            boost::log::trivial::severity_level const& severity_;
        };

        inline logger info() { return logger{boost::log::trivial::info}; }
    }
}

#endif //RETHINKMUD_LOG_H
