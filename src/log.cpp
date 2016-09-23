#include "rethinkmud.h"

#include <boost/log/trivial.hpp>

namespace bl = boost::log;

namespace rethinkmud
{
    namespace log
    {
        namespace
        {
            bl::sources::logger_mt logger_;
        }

        void init()
        {
            BOOST_LOG_TRIVIAL(info) << "Hello world from the logger";
            info() << "Hello again" << ' ' << 1234 << " from logger";
            BOOST_LOG(logger_) << "And again...";
        }

        void clean()
        {

        }

        bl::sources::logger_mt& get_logger()
        {
            return logger_;
        }
    }
}
