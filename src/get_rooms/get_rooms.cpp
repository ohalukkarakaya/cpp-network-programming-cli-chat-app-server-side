#include "get_rooms.h"

bool get_rooms(int clientSocket) {
  std::string response = "[";
  for (auto &room : active_rooms) {
    response += room.getRoomId() + R"(", ")";
  }
  if (send(clientSocket, response.c_str(), response.size(), 0) == -1) {
    std::cerr << "Failed to send response." << std::endl;
    return true;
  }

  return false;
}
