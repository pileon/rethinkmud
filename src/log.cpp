#include "rethinkmud.h"

#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
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
                    // TODO Timestamp
                    // TODO: Channel
                    << '[' << bl::expressions::attr< boost::log::trivial::severity_level >("Severity") << "] "
                    << bl::expressions::smessage
            );

            bl::core::get()->add_sink(sink);

            info() << "Hello world";
        }

        void clean()
        {

        }

        logger_type get_logger([[maybe_unused]] std::string const& name /* = "" */)
        {
            return logger_type{};
        }
    }
}
