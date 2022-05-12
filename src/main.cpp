#include "Config.hpp"
#include "DatagramReceiver.hpp"

#include <fstream>
#include <iostream>

int main() {
    std::ifstream inp;
    inp.open("config.txt");
    Config config = ConfigReader::readConfig(inp);

    if (!config.isValid) {
        std::cerr << "config file is invalid" << std::endl;
        return -1;
    }
    
    DatagramReceiver receiver(1488);
    struct in_addr addr = receiver.getAddr();
    std::cout << addr.s_addr << std::endl;
    while(true) {
        if (receiver.receiveData()) {
            std::cout << "got it\n";
        }
    }

    return 0;
}