#pragma once

#include <fstream>
#include <list>
#include <sys/socket.h>

struct Config {
    bool isValid;
    uint64_t maxRequestsPerSecond;
    uint16_t port;
    std::list<std::string> ipList;
    
    Config(uint64_t mrps, uint16_t port_, std::list<std::string>& iplist_) {
        isValid = true;
        maxRequestsPerSecond = mrps;
        port = port_;
        ipList = iplist_;
    }

    Config (bool valid) {
        isValid = valid;
    }
};

namespace ConfigReader {
    Config readConfig(std::ifstream input);
}