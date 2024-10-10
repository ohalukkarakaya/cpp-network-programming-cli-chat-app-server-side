//
// Created by Ö. Haluk KARAKAYA on 1.10.2024.
//

#include "process_request.h"

void processRequest(int clientSocket, const std::string& request)
{
    std::string userId, userIp, roomId;                                 // Parse required data

    size_t firstSlash = request.find('/');
    size_t secondSlash = request.find('/', firstSlash + 1);
    size_t thirdSlash = request.find('/', secondSlash + 1);

    if(
      firstSlash != std::string::npos
      && secondSlash != std::string::npos
      && thirdSlash != std::string::npos
    )
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
                auto it = std::find_if(                                 // Find room if it exist
                  active_rooms.begin(),
                  active_rooms.end(),
                  [&roomId](
                     const Room& room
                  )
                  {
                    return room.getRoomId() == roomId;
                  }
                );

                std::shared_ptr<Room> room = nullptr;                  // create room as null

                if( it != active_rooms.end() )                         // init room unless new room
                {                                                      // will be cereated
                    it->userJoined(userId, userIp);
                    room = std::make_shared<Room>(*it);
                }
                else                                                    // if room doesn't exist
                {                                                       // create new room
                    auto newRoom = std::make_shared<Room>(roomId);
                    newRoom->userJoined(userId, userIp);
                    active_rooms.push_back(*newRoom);

                    room = newRoom;
                }

                std::string response = "[";

                if( !room )                                             // send response to
                {                                                       // joined user
                    send(clientSocket, "User joined the room.", 21, 0);
                    break;
                }

                                                                        // notify old users about
                                                                        // new user
                const std::vector<RoomMember> members = room->getMembers();

                for( size_t i = 0; i < members.size(); ++i )            // create json like string to return
                {                                                       // old users data to new user
                    const auto& member = members[i];

                    response += R"({ "userId": ")" + member.getUserId() + R"(", "userIp": ")" + member.getUserIp() + "\" }";

                    if( i < members.size() - 1 )
                    {
                        response += ", ";
                    }
                }

                response += "]";

                if( send(clientSocket, response.c_str(), response.size(), 0) == -1 )
                {                                                      // log error if json like data can't send
                    std::cerr << "Failed to send response." << std::endl;
                }
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
