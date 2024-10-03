//
// Created by Ö. Haluk KARAKAYA on 30.09.2024.
//

#include "room.h"

Room::Room(const std::string& id) : roomId(id) {}

void Room::userJoined(const std::string& userId, const std::string& userIp)
{
    RoomMember newRoomMember = RoomMember( userId, userIp );
    members.push_back(newRoomMember);

    notifyUsers(newRoomMember, "JOIN");
}

void Room::notifyUsers(const RoomMember& newRoomMember, const std::string type)
{
    for (const auto& member : members)
    {
        if (member.getUserId() != newRoomMember.getUserId())
        {
            int sock = 0;
            struct sockaddr_in serv_addr;

            if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            {
                std::cerr << "Socket creation error for user: " << member.getUserId() << std::endl;
                continue;
            }

            serv_addr.sin_family = AF_INET;
            serv_addr.sin_port = htons(8080);

            if (inet_pton(AF_INET, member.getUserIp().c_str(), &serv_addr.sin_addr) <= 0)
            {
                std::cerr << "Invalid address / Address not supported for user: " << member.getUserId() << std::endl;
                closeSocket(sock);
                continue;
            }

            if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
            {
                std::cerr << "Connection failed for user: " << member.getUserId() << std::endl;
                closeSocket(sock);
                continue;
            }

            std::string message = "type: " + type + ",userId: " + newRoomMember.getUserId() + ",userIp: " + newRoomMember.getUserIp();

            send(sock, message.c_str(), message.size(), 0);
            std::cout << "Notification sent to user: " << member.getUserId() << std::endl;

            closeSocket(sock);
        }
    }
}

void Room::userLeft(const std::string& userId)
{
    auto it = std::remove_if(
            members.begin(),
            members.end(),
            [&userId](const RoomMember& member)
            {
                return member.getUserId() == userId;
            }
    );

    if (it != members.end())
    {
        members.erase(it, members.end());
        std::cout << userId << " left chat in room " << roomId << std::endl;

        if (members.empty())
        {
            std::cout << "Room " << roomId << " is now empty and will be deleted." << std::endl;
        }
    }
}

void Room::updateUserIp( const std::string& userId, const std::string& newIp )
{
    std::optional<RoomMember> optionalMember = findUser(userId);
    if (!optionalMember)
    {
        return;
    }

    RoomMember member = optionalMember.value();
    member.updateIp( newIp );
}

std::optional<RoomMember> Room::findUser( const std::string &userId )
{
    for( const auto& member : members )
    {
        if( member.getUserId() == userId )
        {
            return member;
        }
    }

    return std::nullopt;
}

const std::string& Room::getRoomId() const
{
    return roomId;
}

const std::vector<RoomMember>& Room::getMembers() const
{
    return members;
}