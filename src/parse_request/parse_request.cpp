#include "parse_request.h"

RequestData* parseRequest(std::string& rawRequest) {
    std::string type, command, userId, userIp, roomId;

    // find first ":"
    size_t colonPos = rawRequest.find(':');

    if (colonPos == std::string::npos) {
        std::cerr << "Missing command separator ':'" << std::endl;
        running = false;
        return nullptr;
    }

    // get type
    type = rawRequest.substr(0, colonPos);

    Command typeValue = getCommandType( type );
    if( typeValue == UNKNOWN )
    {
        // turn empty request data
        return new RequestData();
    }

    // Geri kalan kısmı işle
    std::string remainingRequest = rawRequest.substr(colonPos + 1);

    // Kalan kısmı '/' karakterlerine göre parçala
    size_t firstSlash  = remainingRequest.find('/');
    size_t secondSlash = remainingRequest.find('/',  firstSlash  + 1);
    size_t thirdSlash  = remainingRequest.find('/',  secondSlash + 1);


    if (firstSlash == std::string::npos || secondSlash == std::string::npos || thirdSlash == std::string::npos)
    {
        std::cerr << "Missing Parameter" << std::endl;
        running = false;
        return nullptr;
    }

    command = remainingRequest.substr(0, firstSlash);
    userId = remainingRequest.substr(firstSlash + 1, secondSlash - firstSlash - 1);
    userIp = remainingRequest.substr(secondSlash + 1, thirdSlash - secondSlash - 1);
    roomId = remainingRequest.substr(thirdSlash + 1);

    std::cout << "request received: " << remainingRequest << std::endl;

    auto* data = new RequestData(command, userId, userIp, roomId);
    return data;
}