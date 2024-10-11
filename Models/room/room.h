//
// Created by Ö. Haluk KARAKAYA on 30.09.2024.
//

#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "../room_member/room_member.h"
#include "../../src/send_to_ip/send_to_ip.h"
#include "../../src/scokets_helper/sockets_helper.h"

class Room {
public:
    Room(const std::string& id);

    void userJoined(const std::string& userId, const std::string& userIp);

    void userLeft(const std::string& userId);
    void updateUserIp( const std::string& userId, const std::string& newIp );

    std::optional<RoomMember> findUser(const std::string& userId);

    [[nodiscard]] const std::string& getRoomId() const;
    [[nodiscard]] const std::vector<RoomMember>& getMembers() const;

private:
    std::string roomId;
    std::vector<RoomMember> members;
};

#endif //ROOM_H
