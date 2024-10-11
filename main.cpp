#include <iostream>
#include <thread>
#include <netinet/in.h>
#include <csignal>

#include "src/scokets_helper/sockets_helper.h"
#include "src/handle_client/handle_client.h"

#define PORT 8080

int main()
{
    signal(SIGINT, signalHandler);

    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    initSockets();

    // Create Socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        std::cerr << "Socket creation failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

#if defined(_WIN32) || defined(_WIN64)
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) != 0)
#else
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) != 0)
#endif
    {
        std::cerr << "setsockopt error!" << std::endl;
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
    {
        std::cerr << "Bind failed!" << std::endl;
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        std::cerr << "Listen error!" << std::endl;
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server is listening on port " << PORT << "..." << std::endl;

    while ( running )
    {
        if( (new_socket = accept(server_fd, (struct  sockaddr*)&address, (socklen_t*)&addrlen)) < 0 )
        {
            std::cerr << "Accept Error!" << std::endl;
            close(server_fd);
            continue;
        }

        std::thread( handleClient, new_socket ).detach();
    }

    closeSocket(server_fd);
    return 0;
}
