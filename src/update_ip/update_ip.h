//
// Created by Ö. Haluk KARAKAYA on 10.10.2024.
//

#ifndef UPDATE_IP_H
#define UPDATE_IP_H

#include <iostream>

#include "../../include/global_variables.h"
#include "../../Models/request_data/request_data.h"

bool updateIp(int clientSocket, const std::string& roomId, const std::string& userId, const std::string& userIp);

#endif //UPDATE_IP_H
