//
// Created by Ö. Haluk KARAKAYA on 10.10.2024.
//

#include "parse_request.h"

RequestData* parseRequest( std::string& rawRequest )
{
    std::string userId, userIp, roomId;

    size_t firstSlash = rawRequest.find('/');
    size_t secondSlash = rawRequest.find('/', firstSlash + 1);
    size_t thirdSlash = rawRequest.find('/', secondSlash + 1);

    if( firstSlash == std::string::npos || secondSlash == std::string::npos || thirdSlash == std::string::npos )
    {
        std::cerr << "Missing Parameter" << std::endl;
        running = false;

        return nullptr;
    }

    std::string command = rawRequest.substr(0, firstSlash);
    userId = rawRequest.substr(firstSlash + 1, secondSlash - firstSlash - 1);
    userIp = rawRequest.substr(secondSlash + 1, thirdSlash - secondSlash - 1);
    roomId = rawRequest.substr(thirdSlash + 1);

    auto* data = new RequestData( command, userId, userIp, roomId );

    return data;
}
