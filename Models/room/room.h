//
// Created by Ö. Haluk KARAKAYA on 30.09.2024.
//

#ifndef CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_SERVER_SIDE_ROOM_H
#define CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_SERVER_SIDE_ROOM_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "../room_member/room_member.h"
#include "../../src/send_to_ip/send_to_ip.h"

class Room {
public:
    Room(const std::string& id);

    void userJoined(const std::string& mainUserId, const std::string& userId, const std::string& userIp);
    void userLeft(const std::string& userId);
    [[nodiscard]] const std::string& getRoomId() const;
    const std::vector<RoomMember>& getMembers() const;

    std::optional<RoomMember> findUser(const std::string& userId);
    void updateUserIp( const std::string& userId, const std::string& newIp );

private:
    std::string roomId;
    std::vector<RoomMember> members;
};

#endif //CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_SERVER_SIDE_ROOM_H
