//
// Created by Ö. Haluk KARAKAYA on 10.10.2024.
//

#ifndef JOIN_ROOM_H
#define JOIN_ROOM_H

#include <iostream>

#include "../../include/global_variables.h"

bool joinRoom(int clientSocket, const std::string& roomId, const std::string& userId, const std::string& userIp );

#endif //JOIN_ROOM_H
