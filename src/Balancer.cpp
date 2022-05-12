#include "Balancer.hpp"

#include <ctime>
#include <iostream>
#include <utility>

static struct sockaddr_in getIpAddress(const std::string &ipAddress) {
    struct sockaddr_in sa;
    int portSepPosition = ipAddress.find(":");
    if (portSepPosition == -1) {
        std::cerr << "Port should be specified for " << ipAddress << std::endl;
        exit(-1);
    }

    auto portStr = ipAddress.substr(portSepPosition + 1,
                                    ipAddress.length() - portSepPosition);
    uint16_t port = std::stoi(portStr);
    if (!port) {
        std::cerr << "Illegal port " << portStr << std::endl;
        exit(-1);
    }

    int result = inet_pton(
        AF_INET, ipAddress.substr(0, portSepPosition).c_str(), &(sa.sin_addr));
    sa.sin_family = AF_INET;
    sa.sin_port = port;
    if (!result) {
        std::cerr << "Address " << ipAddress << " is incorrect\n";
        exit(-1);
    }
    return sa;
}

Balancer::Balancer(const Config &config) : socket(config.port) {
    maxRequestsPerSecond = config.maxRequestsPerSecond;
    port = config.port;
    for (auto s : config.ipList) {
        ipList.push_back(getIpAddress(s));
    }
    currentAddr = ipList.begin();
}

void Balancer::processNextRequest() {
    ssize_t datagramLength = socket.receiveData();
    time_t now = std::time(NULL);
    while (!timeQueue.empty() && now - timeQueue.front() > 1) {
        timeQueue.pop_front();
    }
    if (timeQueue.size() >= maxRequestsPerSecond) {
        std::cerr << "request rejectded\n";
        return;
    }
    timeQueue.push_back(now);
    socket.sendData(*currentAddr, socket.getData(), datagramLength);

    char ip[20];
    inet_ntop(AF_INET, &((*currentAddr).sin_addr), ip, INET_ADDRSTRLEN);
    std::cerr << "redirected to " << ip << ":" << (*currentAddr).sin_port
              << std::endl;
    currentAddr++;
    if (currentAddr == ipList.end()) {
        currentAddr = ipList.begin();
    }
}