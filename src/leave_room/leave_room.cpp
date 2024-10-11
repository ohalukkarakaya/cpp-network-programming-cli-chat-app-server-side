//
// Created by Ö. Haluk KARAKAYA on 11.10.2024.
//

#include "leave_room.h"

bool leaveRoom( int clientSocket, const std::string& roomId, const std::string& userId )
{
    for( Room& room : active_rooms )
    {
        if( room.getRoomId() == roomId )
        {
            room.userLeft( userId );
            send(clientSocket, "User left the room.", 19, 0);

            return false;
        }
    }
    return true;
}