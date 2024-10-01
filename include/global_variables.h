//
// Created by Ö. Haluk KARAKAYA on 1.10.2024.
//

#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include "../Models/room/room.h"

std::vector<Room> active_rooms;
std::mutex roomMutex;

#endif //GLOBAL_VARIABLES_H
