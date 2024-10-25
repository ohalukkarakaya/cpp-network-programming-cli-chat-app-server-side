#include "room_manager.h"

void room_manager::addRoom(const Room& room) {
    rooms.push_back(room);
}

void room_manager::deleteRoom(const std::string& roomId) {
    auto it = std::remove_if(rooms.begin(), rooms.end(),
                             [&roomId](const Room& room) {
                                 return room.getRoomId() == roomId;
                             });

    if (it != rooms.end()) {
        rooms.erase(it, rooms.end());
    }
}

std::vector<Room> room_manager::getRooms() const {
    return rooms;
}
