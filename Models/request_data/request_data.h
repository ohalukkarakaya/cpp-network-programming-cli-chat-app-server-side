//
// Created by Ö. Haluk KARAKAYA on 10.10.2024.
//

#ifndef REQUEST_DATA_H
#define REQUEST_DATA_H

#include <iostream>

class RequestData
{
public:
    RequestData(std::string command, std::string userId, std::string userIp, std::string roomId);

    std::string& getCommand();
    std::string& getUserId();
    std::string& getUserIp();
    std::string& getRoomId();

private:
    std::string command;
    std::string userId;
    std::string userIp;
    std::string roomId;
};

#endif //REQUEST_DATA_H
