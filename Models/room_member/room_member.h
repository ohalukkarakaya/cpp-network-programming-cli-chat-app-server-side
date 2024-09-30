//
// Created by Ö. Haluk KARAKAYA on 30.09.2024.
//

#ifndef CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_SERVER_SIDE_ROOM_MEMBER_H
#define CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_SERVER_SIDE_ROOM_MEMBER_H

#include <iostream>
#include <string>
#include <ctime>

class RoomMember {
public:
    RoomMember(std::string  userId, std::string  userIp);

    [[nodiscard]] const std::string& getUserId() const;
    [[nodiscard]] const std::string& getUserIp() const;
    time_t getJoinDate() const;

    void updateIp( const std::string& newIp );

private:
    std::string userId;
    std::string userIp;
    time_t joinDate;
};

#endif //CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_SERVER_SIDE_ROOM_MEMBER_H
