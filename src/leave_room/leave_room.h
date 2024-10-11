//
// Created by Ö. Haluk KARAKAYA on 11.10.2024.
//

#ifndef LEAVE_ROOM_H
#define LEAVE_ROOM_H

#include <iostream>

#include "../../include/global_variables.h"

bool leaveRoom( int clientSocket, const std::string& roomId, const std::string& userId );

#endif //LEAVE_ROOM_H
