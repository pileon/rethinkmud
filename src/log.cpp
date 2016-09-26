#include "rethinkmud.h"

#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/core/null_deleter.hpp>

namespace bl = boost::log;

namespace rethinkmud
{
    namespace log
    {
        void init()
        {
            bl::add_common_attributes();

            using text_sink_type = bl::sinks::synchronous_sink<bl::sinks::text_ostream_backend>;
            auto sink = boost::make_shared<text_sink_type>();

            sink->locked_backend()->add_stream(boost::shared_ptr< std::ostream >(&std::clog, boost::null_deleter()));

            sink->set_formatter(
                bl::expressions::stream
                    << bl::expressions::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f") << " :: "
                    << '[' << bl::trivial::severity << " - " << bl::expressions::attr<std::string>("Channel") << "] "
                    << bl::expressions::smessage
            );

            bl::core::get()->add_sink(sink);
        }

        void clean()
        {

        }

        logger_type get_logger([[maybe_unused]] std::string const& name /* = "general" */)
        {
            return logger_type{
                bl::keywords::channel = name
            };
        }
    }
}
