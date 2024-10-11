#include "handle_client.h"

void handleClient( int clientSocket )
{
    char buffer[1024] = {0};
    int valread = read(clientSocket, buffer, 1024);

    if ( valread < 0 )
    {
        std::cerr << "Read error!" << std::endl;
        closeSocket(clientSocket);
        return;
    }

    std::string request(buffer);

    processRequest( clientSocket, request );
    closeSocket( clientSocket );
}