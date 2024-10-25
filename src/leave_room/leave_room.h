#ifndef LEAVE_ROOM_H
#define LEAVE_ROOM_H

#include <iostream>

#include "../../include/global_variables.h"

#include "../send_to_ip/send_to_ip.h"

bool leaveRoom( int clientSocket, const std::string& roomId, const std::string& userId );

#endif //LEAVE_ROOM_H
