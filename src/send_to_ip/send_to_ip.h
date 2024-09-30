//
// Created by Ö. Haluk KARAKAYA on 30.09.2024.
//

#ifndef CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_SERVER_SIDE_SEND_TO_IP_H
#define CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_SERVER_SIDE_SEND_TO_IP_H

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>

void sendToIp(const std::string& ip, const std::string& message, const std::string& type = "message");

#endif //CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_SERVER_SIDE_SEND_TO_IP_H
