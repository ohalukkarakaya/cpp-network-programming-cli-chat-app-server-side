#include "handle_client.h"

void handleClient(int clientSocket) {
    char buffer[1024] = {0};
    int valread = read(clientSocket, buffer, 1024);

    if (valread <= 0) {
        std::cerr << "Read error or connection lost!" << std::endl;
        closeSocket(clientSocket);
        return;
    }

    std::string request(buffer);

    RequestData requestData;
    processRequest(clientSocket, request, requestData);

    std::string roomId = requestData.getRoomId();
    std::string userId = requestData.getUserId();

    while (running) {
        int result = recv(clientSocket, buffer, sizeof(buffer), MSG_DONTWAIT);

        if (result == 0) {
            std::cerr << "Connection lost for client: " << clientSocket << std::endl;
            leaveRoom(clientSocket, roomId, userId);
            break;
        } else if (result == -1 && errno != EWOULDBLOCK) {
            std::cerr << "Socket error!" << std::endl;
            leaveRoom(clientSocket, roomId, userId);
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    closeSocket(clientSocket);
}
