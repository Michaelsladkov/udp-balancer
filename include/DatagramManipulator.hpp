#pragma once

#include <arpa/inet.h>
#include <fstream>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define UDP_PACKET_MAX_SIZE 65530

class DatagramManipulator {
    int socketDescriptor;
    struct sockaddr_in serAddr;
    char buff[UDP_PACKET_MAX_SIZE + 1] = {0};

  public:
    DatagramManipulator(uint16_t port);
    ~DatagramManipulator();
    ssize_t receiveData();
    char *getData();
    struct in_addr getAddr();
    void sendData(struct sockaddr_in addr, char *data, size_t size);
};