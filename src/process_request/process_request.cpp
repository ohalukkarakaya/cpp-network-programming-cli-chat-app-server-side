//
// Created by Ö. Haluk KARAKAYA on 1.10.2024.
//

#include "process_request.h"

void processRequest(int clientSocket, const std::string& request)
{

    std::string mutableRequest = request;
    RequestData* requestData = parseRequest( mutableRequest );

    Command cmdType = getCommandType( requestData->getCommand() );
    std::string roomId = requestData->getRoomId();
    std::string userId = requestData->getUserId();
    std::string userIp = requestData->getUserIp();

    switch( cmdType )
    {
        case JOINROOM:
        {
            bool didFail = joinRoom( clientSocket, roomId, userId, userIp );

            if( didFail )
            {
                std::cerr << "Error: JOIN ROOM " << std::endl;
            }
            break;
        }
        case UPDATEIP:
        {

            bool didFail = updateIp( clientSocket, roomId, userId, userIp );

            if( didFail )
            {
                std::cerr << "Error: UPDATE IP " << std::endl;
            }
            break;
        }
        case LEAVEROOM:
        {
            for (Room& room : active_rooms)
            {
                if (room.getRoomId() == roomId)
                {
                    room.userLeft(userId);
                    send(clientSocket, "User left the room.", 19, 0);
                    return;
                }
            }
            send(clientSocket, "Room not found.", 15, 0);
            break;
        }
        case UNKNOWN:
        default:
            send(clientSocket, "Unknown command.", 16, 0);
            break;
    }
}
