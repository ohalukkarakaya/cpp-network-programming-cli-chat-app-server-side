#include "leave_room.h"

bool leaveRoom( int clientSocket, const std::string& roomId, const std::string& userId )
{
    for( Room& room : active_rooms )
    {
        if( room.getRoomId() == roomId )
        {
            room.userLeft( userId );
            send(clientSocket, "User left the room.", 19, 0);

            for( const RoomMember& roomMember : room.getMembers() )
            {
                std::string message = "LEAVEROOM:" + userId + "/" + roomMember.getUserIp() + "/" + roomId;
                sendToIp(roomMember.getUserIp(), message, "LEAVEROOM");
            }

            return false;
        }
    }
    return true;
}