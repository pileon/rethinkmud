#ifndef RETHINKMUD_LOG_H
#define RETHINKMUD_LOG_H

#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>

namespace rethinkmud
{
    namespace log
    {
        void init();
        void clean();

        using logger_type = boost::log::sources::severity_channel_logger_mt<boost::log::trivial::severity_level>;
        logger_type get_logger(std::string const& name = "general");

        class logger
        {
        public:
            logger(boost::log::trivial::severity_level severity, std::string const& channel = "general")
                : logger_{get_logger(channel)},
                  rec_{logger_.open_record(boost::log::keywords::severity = severity)},
                  ros_{rec_}
            {}

            logger(logger&& l)
                : logger_{std::move(l.logger_)},
                  rec_{std::move(l.rec_)},
                  ros_{rec_}
            {}

            ~logger()
            {
                ros_.flush();
                logger_.push_record(std::move(rec_));
            }

            template<typename T>
            logger& operator<<(T const& x)
            {
                ros_ << x;
                return *this;
            }

        private:
            logger_type logger_;
            boost::log::record rec_;
            boost::log::record_ostream ros_;
        };

        inline logger info   (std::string const& channel = "general") { return logger{boost::log::trivial::info   , channel}; }
        inline logger debug  (std::string const& channel = "general") { return logger{boost::log::trivial::debug  , channel}; }
        inline logger error  (std::string const& channel = "general") { return logger{boost::log::trivial::error  , channel}; }
        inline logger trace  (std::string const& channel = "general") { return logger{boost::log::trivial::trace  , channel}; }
        inline logger warning(std::string const& channel = "general") { return logger{boost::log::trivial::warning, channel}; }
        inline logger fatal  (std::string const& channel = "general") { return logger{boost::log::trivial::fatal  , channel}; }
    }
}

#endif //RETHINKMUD_LOG_H
