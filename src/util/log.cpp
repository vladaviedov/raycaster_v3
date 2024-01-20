#include "log.hpp"

#include <map>

using namespace rc3::log;

// Externs
logstream rc3::log::debug(loglvl::DEBUG);
logstream rc3::log::info(loglvl::INFO);
logstream rc3::log::warn(loglvl::WARN);
logstream rc3::log::error(loglvl::ERROR);
logstream rc3::log::fatal(loglvl::FATAL);

// Log level to string map
static const std::map<loglvl, const char *> lvl_map = {
	{ loglvl::DEBUG, "DEBUG" },
	{ loglvl::INFO, "INFO " },
	{ loglvl::WARN, "WARN " },
	{ loglvl::ERROR, "ERROR" },
	{ loglvl::FATAL, "FATAL" }
};

const char *logstream::lvl_string() const {
	return lvl_map.find(lvl)->second;
}
