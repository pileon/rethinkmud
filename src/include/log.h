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
        logger_type get_logger(std::string const& name = "");

        class logger
        {
        public:
            logger(boost::log::trivial::severity_level severity)
                : logger_{get_logger()},
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

        inline logger info   () { return logger{boost::log::trivial::info   }; }
        inline logger debug  () { return logger{boost::log::trivial::debug  }; }
        inline logger error  () { return logger{boost::log::trivial::error  }; }
        inline logger trace  () { return logger{boost::log::trivial::trace  }; }
        inline logger warning() { return logger{boost::log::trivial::warning}; }
        inline logger fatal  () { return logger{boost::log::trivial::fatal  }; }
    }
}

#endif //RETHINKMUD_LOG_H
