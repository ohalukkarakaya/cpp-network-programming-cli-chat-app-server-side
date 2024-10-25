#ifndef ROOM_MANAGER_H
#define ROOM_MANAGER_H

#include <vector>
#include <string>

#include "../room/room.h"

class room_manager {
public:
    void addRoom(const Room& room);
    void deleteRoom(const std::string& roomId);
    [[nodiscard]] std::vector<Room> getRooms() const;

private:
    std::vector<Room> rooms;
};

#endif // ROOM_MANAGER_H
