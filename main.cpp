#include <iostream>
#include <thread>

#include "Models/room/room.h"
#include "src/handle_client/handle_client.h"

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Create Socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        std::cerr << "Socket creation failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
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

    while ( true )
    {
        if((new_socket = accept(server_fd, (struct  sockaddr*)&address, (socklen_t*)&addrlen)) < 0 )
        {
            std::cerr << "Accept Error!" << std::endl;
            close(server_fd);
            continue;
        }

        std::thread( handleClient, new_socket ).detach();
    }

    close(server_fd);
    return 0;
}
