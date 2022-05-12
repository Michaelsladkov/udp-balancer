#include "DatagramReceiver.hpp"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

DatagramReceiver::DatagramReceiver(uint16_t port) {
    socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketDescriptor < 0) {
        perror("socket creation error...\n");
        exit(-1);
    }
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(port);
    serAddr.sin_addr.s_addr = INADDR_ANY;
    if ((bind(socketDescriptor, (struct sockaddr *)&serAddr, sizeof(serAddr))) <
        0) {
        perror("binding error...\n");
        close(socketDescriptor);
        exit(-1);
    }
}

bool DatagramReceiver::receiveData() {
    ssize_t readStatus =
        recv(socketDescriptor, buff, UDP_PACKET_MAX_SIZE, 0);
    if (readStatus < 0) {
        return false;
    }
    return true;
}

struct in_addr DatagramReceiver::getAddr() {
    return serAddr.sin_addr;
}