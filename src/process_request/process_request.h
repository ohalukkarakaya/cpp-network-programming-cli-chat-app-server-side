//
// Created by Ö. Haluk KARAKAYA on 1.10.2024.
//

#ifndef PROCESS_REQUEST_H
#define PROCESS_REQUEST_H

#include <iostream>
#include <mutex>

#include "../../Models/request_type_enum/request_type_enum.h"
#include "../../include/global_variables.h"

#include "../parse_request/parse_request.h"

#include "../get_rooms/get_rooms.h"
#include "../join_room/join_room.h"
#include "../leave_room/leave_room.h"
#include "../update_ip/update_ip.h"

void processRequest(int clientSocket, const std::string &request, RequestData& requestData);

#endif // PROCESS_REQUEST_H
