#include "spdlog/spdlog.h"
namespace logger {
    auto console = spdlog::stdout_logger_mt("console");
}
