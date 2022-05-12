#pragma once

#include "Config.hpp"

#include "DatagramManipulator.hpp"

#include <ctime>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

class Balancer {
    uint64_t maxRequestsPerSecond;
    uint16_t port;
    std::list<struct sockaddr_in> ipList;
    std::list<struct sockaddr_in>::iterator currentAddr;
    DatagramManipulator socket;
    std::list<time_t> timeQueue;

  public:
    explicit Balancer(const Config &config);
    void processNextRequest();
};
