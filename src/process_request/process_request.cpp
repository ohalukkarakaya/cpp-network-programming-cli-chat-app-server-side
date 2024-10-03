//
// Created by Ö. Haluk KARAKAYA on 1.10.2024.
//

#include "process_request.h"

void processRequest(int clientSocket, const std::string& request)
{
    std::string userId, userIp, roomId;

    size_t firstSlash = request.find('/');
    size_t secondSlash = request.find('/', firstSlash + 1);
    size_t thirdSlash = request.find('/', secondSlash + 1);

    if (firstSlash != std::string::npos && secondSlash != std::string::npos && thirdSlash != std::string::npos)
    {
        std::string command = request.substr(0, firstSlash);
        userId = request.substr(firstSlash + 1, secondSlash - firstSlash - 1);
        userIp = request.substr(secondSlash + 1, thirdSlash - secondSlash - 1);
        roomId = request.substr(thirdSlash + 1);

        std::lock_guard<std::mutex> lock(roomMutex);

        Command cmdType = getCommandType(command);

        switch( cmdType )
        {
            case JOINROOM:
            {
                auto it = std::find_if(active_rooms.begin(), active_rooms.end(), [&roomId](const Room& room) { return room.getRoomId() == roomId; });

                if ( it != active_rooms.end() )
                {
                    it->userJoined(userId, userId, userIp);
                }
                else
                {
                    Room newRoom(roomId);
                    newRoom.userJoined(userId, userId, userIp);
                    active_rooms.push_back(newRoom);
                }

                send(clientSocket, "User joined the room.", 21, 0);
                break;
            }
            case UPDATEIP:
            {
                for (auto& room : active_rooms)
                {
                    if (room.getRoomId() == roomId)
                    {
                        room.updateUserIp(userId, userIp);
                        send(clientSocket, "IP updated successfully.", 23, 0);
                        return;
                    }
                }

                send(clientSocket, "Room not found.", 15, 0);
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
}
