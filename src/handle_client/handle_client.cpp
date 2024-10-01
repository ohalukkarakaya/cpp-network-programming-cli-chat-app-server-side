#include "handle_client.h"

void handleClient( int clientSocket )
{
    char buffer[1024] = {0};
    int valread = read(clientSocket, buffer, 1024);
    std::string request(buffer);

    processRequest(clientSocket, request);
    close(clientSocket);
}