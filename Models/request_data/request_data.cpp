//
// Created by Ö. Haluk KARAKAYA on 10.10.2024.
//

#include "request_data.h"

RequestData::RequestData(std::string command, std::string userId, std::string userIp, std::string roomId)
        : command(std::move(command)), userId(std::move(userId)), userIp(std::move(userIp)), roomId(std::move(roomId)) {}

std::string& RequestData::getCommand()
{
    return command;
}

std::string& RequestData::getUserId()
{
    return userId;
}

std::string& RequestData::getUserIp()
{
    return userIp;
}

std::string& RequestData::getRoomId()
{
    return roomId;
}
