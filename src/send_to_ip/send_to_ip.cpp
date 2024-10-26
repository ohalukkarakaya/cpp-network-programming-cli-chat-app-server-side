#include "send_to_ip.h"

void sendToIp(const std::string& ip, const std::string& message, const std::string& type, int port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Socket creation failed" << std::endl;
        return;
    }

    sockaddr_in serverAddr{};
    std::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port   = htons(port);
    inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr);

    if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
    {
        std::cerr << "Connection to " << ip << " failed" << std::endl;
        close(sock);
        return;
    }

    std::string fullMessage = type + ":" + message;
    send(sock, fullMessage.c_str(), fullMessage.size(), 0);
    close(sock);
}