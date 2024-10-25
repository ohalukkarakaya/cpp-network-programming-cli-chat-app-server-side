#include "room.h"

void Room::userJoined(const std::string& userId, const std::string& userIp)
{
    RoomMember newRoomMember = RoomMember( userId, userIp );
    members.push_back(newRoomMember);


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
            auto it = std::remove_if(active_rooms.begin(), active_rooms.end(),
                                     [roomId = this->roomId](const Room& room) {
                                         return room.getRoomId() == roomId;
                                     });
            active_rooms.erase(it, active_rooms.end());
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