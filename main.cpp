#include <iostream>
#include <thread>
#include <netinet/in.h>
#include <csignal>

#include "src/scokets_helper/sockets_helper.h"
#include "src/handle_client/handle_client.h"
#include "src/get_ip_adress/get_ip_adress.h"

#define PORT 9090

int main()
{
    running = true;

    signal( SIGINT, signalHandler );

    int                server_fd, new_socket;
    struct sockaddr_in address;
    int                opt                       = 1;
    int                addrlen                   = sizeof(address);

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
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) != 0)
#endif
    {
        std::cerr << "setsockopt error!" << strerror(errno) << std::endl;
        close( server_fd    );
        exit(  EXIT_FAILURE );
    }

    address.sin_family      = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port        = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
    {
        std::cerr << "Bind failed!" << std::endl;
        close( server_fd    );
        exit(  EXIT_FAILURE );
    }

    if (listen(server_fd, 3) < 0)
    {
        std::cerr << "Listen error!" << std::endl;
        close( server_fd    );
        exit(  EXIT_FAILURE );
    }

    std::cout << "Server is listening on port " << PORT << "..." << std::endl;

    std::string ipAdress = getIPAddress();
    std::cout << "ip adress is: " << ipAdress << std::endl;

    while ( running )
    {
        // Set timeout for accept
        fd_set    readfds;
        FD_ZERO(  &readfds            );
        FD_SET(   server_fd, &readfds );

        struct timeval timeout;
        timeout.tv_sec  = 1;  // 1 sec
        timeout.tv_usec = 0;

        int activity = select(server_fd + 1, &readfds, NULL, NULL, &timeout);

        if (activity < 0) {
            if(running) std::cerr << "Select error!" << std::endl;
            continue;
        }

        if (FD_ISSET(server_fd, &readfds)) {
            new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
            if (new_socket < 0) {
                std::cerr << "Accept Error!" << std::endl;
                continue;
            }

            std::thread(handleClient, new_socket).detach();
        }

        if( !running ) break;
    }

    closeSocket(server_fd);
    return 0;
}
