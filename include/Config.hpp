#pragma once

#include <fstream>
#include <list>
#include <sys/socket.h>

struct Config {
    uint64_t maxRequestsPerSecond;
    uint16_t port;
    std::list<struct sockadr_in> ipList;
};

namespace ConfigReader {
    Config readConfig(std::fstream input);
}