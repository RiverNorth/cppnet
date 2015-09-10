//
// Created by root on 9/10/15.
//

#ifndef CPPNET_SPDLOG_H
#define CPPNET_SPDLOG_H
#include <iostream>
#include "spdlog/spdlog.h"
namespace logger{
    extern std::shared_ptr<spdlog::logger> console;
}

#endif //CPPNET_SPDLOG_H
