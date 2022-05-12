#pragma once

#include <arpa/inet.h>
#include <fstream>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define UDP_PACKET_MAX_SIZE 65535

class DatagramReceiver {
    int socketDescriptor;
    struct sockaddr_in serAddr;
    uint8_t buff[UDP_PACKET_MAX_SIZE + 1];

  public:
    DatagramReceiver(uint16_t port);
    bool receiveData();
    uint8_t *getData();
    struct in_addr getAddr();
};