//
// Created by Ö. Haluk KARAKAYA on 10.10.2024.
//

#include "request_data.h"

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
