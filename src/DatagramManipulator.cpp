#include "DatagramManipulator.hpp"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

DatagramManipulator::DatagramManipulator(uint16_t port) {
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

DatagramManipulator::~DatagramManipulator() { close(socketDescriptor); }

ssize_t DatagramManipulator::receiveData() {
    ssize_t readStatus = recv(socketDescriptor, buff, UDP_PACKET_MAX_SIZE, 0);
    if (readStatus < 0) {
        perror("reading error on receive\n");
        close(socketDescriptor);
        exit(-1);
    }
    return readStatus;
}

void DatagramManipulator::sendData(struct sockaddr_in addr, char *data,
                                   size_t size) {
    if (sendto(socketDescriptor, data, size, 0, (struct sockaddr *)&addr,
               sizeof(addr)) < 0) {
        perror("sending error...\n");
        close(socketDescriptor);
        exit(-1);
    }
}

struct in_addr DatagramManipulator::getAddr() {
    return serAddr.sin_addr;
}

char *DatagramManipulator::getData() { return buff; }