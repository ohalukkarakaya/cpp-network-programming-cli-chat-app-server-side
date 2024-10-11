//
// Created by Ö. Haluk KARAKAYA on 10.10.2024.
//

#include "join_room.h"

bool joinRoom(int clientSocket, const std::string& roomId, const std::string& userId, const std::string& userIp )
{
    auto it = std::find_if( active_rooms.begin(), active_rooms.end(), [&roomId]( const Room& room ){ return room.getRoomId() == roomId; } );

    std::shared_ptr<Room> room = nullptr;

    std::string response = "[";

    if( it != active_rooms.end() )
    {
        it->userJoined(userId, userIp);
        room = std::make_shared<Room>(*it);
    }
    else
    {
        auto newRoom = std::make_shared<Room>(roomId);
        newRoom->userJoined(userId, userIp);
        active_rooms.push_back(*newRoom);

        room = newRoom;
    }

    if( !room )                                             // send response to
    {                                                       // joined user
        send(clientSocket, "User joined the room.", 21, 0);
        return false;
    }

    const std::vector<RoomMember> members = room->getMembers();

    for( size_t i = 0; i < members.size(); ++i )
    {
        const auto& member = members[i];

        response += R"({ "userId": ")" + member.getUserId() + R"(", "userIp": ")" + member.getUserIp() + "\" }";

        if( i < members.size() - 1 )
        {
            response += ", ";
        }

        response += "]";

        if( send(clientSocket, response.c_str(), response.size(), 0) == -1 )
        {
            std::cerr << "Failed to send response." << std::endl;
            return true;
        }
        return false;
    }
    return true;
}
