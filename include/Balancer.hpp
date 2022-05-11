#pragma once

#include "Config.hpp"

class Balancer {
    uint64_t maxRequestsPerSecond;
    uint16_t port;
    std::list<struct sockadr_in> ipList;
public:
    Balancer(Config config);
    Balancer(uint64_t mrps, uint16_t port_, std::list<struct sockadr_in> ipList_);
    void start();
}
