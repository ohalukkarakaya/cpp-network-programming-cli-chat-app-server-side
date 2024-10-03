//
// Created by Ö. Haluk KARAKAYA on 3.10.2024.
//

#ifndef SOCKETS_HELPER_H
#define SOCKETS_HELPER_H

#include <iostream>
#include "../../include/global_variables.h"

#if defined(_WIN32) || defined(_WIN64)
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")  // Winsock library
#else
#include <unistd.h>  // for close()
#endif

void initSockets();

void closeSocket(int socket_fd);

void signalHandler( int signum );

#endif // SOCKETS_HELPER_H
