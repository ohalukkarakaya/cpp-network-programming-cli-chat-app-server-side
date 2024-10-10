//
// Created by Ö. Haluk KARAKAYA on 1.10.2024.
//

#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

class Room;

#include "../Models/room/room.h"

inline std::vector<Room> active_rooms;
inline std::mutex roomMutex;
inline bool running = true;

#endif //GLOBAL_VARIABLES_H
