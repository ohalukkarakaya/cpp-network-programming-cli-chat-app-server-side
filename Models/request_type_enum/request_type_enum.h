//
// Created by Ö. Haluk KARAKAYA on 1.10.2024.
//

#ifndef REQUEST_TYPE_ENUM_H
#define REQUEST_TYPE_ENUM_H

#include <iostream>

enum Command {
    JOINROOM,
    UPDATEIP,
    LEAVEROOM,
    UNKNOWN
};

Command getCommandType(const std::string& command)

#endif //REQUEST_TYPE_ENUM_H