//
// Created by Ö. Haluk KARAKAYA on 10.10.2024.
//

#ifndef PARSE_REQUEST_H
#define PARSE_REQUEST_H

#include "../../include/global_variables.h"
#include "../../Models/request_data/request_data.h"
#include "../../Models/request_type_enum/request_type_enum.h"

RequestData* parseRequest( std::string& rawRequest );

#endif //PARSE_REQUEST_H
