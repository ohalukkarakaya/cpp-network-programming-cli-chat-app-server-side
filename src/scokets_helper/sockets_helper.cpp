//
// Created by Ö. Haluk KARAKAYA on 3.10.2024.
//

#include "sockets_helper.h"

void initSockets()
{
#if defined(_WIN32) || defined(_WIN64)
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        exit(EXIT_FAILURE);
    }
#endif
}

void closeSocket(int socket_fd)
{
#if defined(_WIN32) || defined(_WIN64)
    closesocket(socket_fd);
    WSACleanup();
#else
    close(socket_fd);
#endif
}

void signalHandler( int signum )
{
    std::cout << "Interrupt signal (" << signum << ") received.\n";
    running = false;
}
