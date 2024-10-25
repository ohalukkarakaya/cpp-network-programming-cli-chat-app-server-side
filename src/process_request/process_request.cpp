#include "process_request.h"
#include <ostream>

void processRequest(int clientSocket, const std::string &request, RequestData& requestData) {

  std::string mutableRequest = request;
  RequestData *parsedData = parseRequest(mutableRequest);

  if( parsedData->getCommand() == "" )
  {
      delete parsedData;
      return;
  }

  requestData = *parsedData;

  Command cmdType = getCommandType(requestData.getCommand());
  std::string roomId = requestData.getRoomId();
  std::string userId = requestData.getUserId();
  std::string userIp = requestData.getUserIp();

  switch (cmdType) {
  case GETROOMS: {
    bool didOperationFailed = get_rooms(clientSocket);

    if (didOperationFailed) {
      std::cerr << "Error: GET ROOMS" << std::endl;
    }
    break;
  }
  case JOINROOM: {
    bool didOperationFailed = joinRoom(clientSocket, roomId, userId, userIp);

    if (didOperationFailed) {
      std::cerr << "Error: JOIN ROOM " << std::endl;
    }
    break;
  }
  case UPDATEIP: {

    bool didOperationFailed = updateIp(clientSocket, roomId, userId, userIp);

    if (didOperationFailed) {
      std::cerr << "Error: UPDATE IP " << std::endl;
    }
    break;
  }
  case LEAVEROOM: {
    bool didOperationFailed = leaveRoom(clientSocket, roomId, userId);

    if (didOperationFailed) {
      std::cerr << "Error: LEAVE ROOM " << std::endl;
    }
    break;
  }
  case UNKNOWN:
  default:
    send(clientSocket, "Unknown command.", 16, 0);
    break;
  }

  delete parsedData;
}
