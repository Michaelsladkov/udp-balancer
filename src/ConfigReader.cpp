#include "Config.hpp"

Config ConfigReader::readConfig(std::ifstream &input) {
    uint64_t mrps;
    input >> mrps;
    if (!mrps) {
        return Config(false);
    }
    uint16_t port;
    input >> port;
    if (!port) {
        return Config(false);
    }
    std::list<std::string> ipList;
    std::string maybeIp;
    while (input >> maybeIp) {
        ipList.push_back(maybeIp);
    }
    return Config(mrps, port, ipList);
}