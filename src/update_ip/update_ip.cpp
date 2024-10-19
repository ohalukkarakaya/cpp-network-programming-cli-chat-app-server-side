//
// Created by Ö. Haluk KARAKAYA on 10.10.2024.
//

#include "update_ip.h"

bool updateIp( int clientSocket, const std::string& roomId, const std::string& userId, const std::string& userIp )
{
    for (auto& room : active_rooms)
    {
        if (room.getRoomId() == roomId)
        {
            room.updateUserIp( userId, userIp );
            send( clientSocket, "IP updated successfully.", 23, 0 );
            return false;
        }
    }

    send(clientSocket, "Room not found.", 15, 0);
    return true;
}
