#include "Balancer.hpp"
#include "Config.hpp"

#include <fstream>
#include <iostream>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv) {
    std::ifstream inp;
    if (argc < 2)
        inp.open("config.txt");
    else
        inp.open(argv[1]);
    Config config = ConfigReader::readConfig(inp);

    if (!config.isValid) {
        std::cerr << "config file is invalid" << std::endl;
        return -1;
    }

    Balancer balancer(config);

    while (true) {
        balancer.processNextRequest();
    }

    return 0;
}