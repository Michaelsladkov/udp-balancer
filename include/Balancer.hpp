#pragma once

#include "Config.hpp"

class Balancer {
    uint64_t maxRequestsPerSecond;
    uint16_t port;
    std::list<struct sockadr_in> ipList;

  public:
    Balancer(const Config &config);
    Balancer(const uint64_t mrps, const uint16_t port_,
             cont std::list<struct sockadr_in> &ipList_);
    void start();
}
