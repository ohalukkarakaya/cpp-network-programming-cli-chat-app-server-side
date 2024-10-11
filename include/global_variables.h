//
// Created by Ö. Haluk KARAKAYA on 1.10.2024.
//

#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

class Room;

#include "../Models/room/room.h"

#define BOLD_RED "\033[1;31m"
#define RESET "\033[0m"

inline std::vector<Room> active_rooms;
inline std::mutex roomMutex;
inline volatile bool running;;

#endif //GLOBAL_VARIABLES_H
