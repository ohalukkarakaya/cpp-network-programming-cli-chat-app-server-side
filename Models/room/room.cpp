//
// Created by Ö. Haluk KARAKAYA on 30.09.2024.
//

#include "room.h"

Room::Room(const std::string& id) : roomId(id) {}

void Room::userJoined(const std::string& mainUserId, const std::string& userId, const std::string& userIp)
{
    members.emplace_back(userId, userIp);
    if( mainUserId != userId )
    {
        std::cout << "\033[33m" << userId << "\033[1;34m" << " joined chat in room " << "\033[33m" << roomId << "\033[0m" << std::endl;
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

const std::string& Room::getRoomId() const
{
    return roomId;
}

const std::vector<RoomMember>& Room::getMembers() const
{
    return members;
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