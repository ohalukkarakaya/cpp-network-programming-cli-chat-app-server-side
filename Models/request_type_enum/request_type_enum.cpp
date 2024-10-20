#include "request_type_enum.h"

Command getCommandType(const std::string &command) {
  if (command == "GETROOMS")
    return GETROOMS;
  if (command == "JOINROOM")
    return JOINROOM;
  if (command == "UPDATEIP")
    return UPDATEIP;
  if (command == "LEAVEROOM")
    return LEAVEROOM;
  return UNKNOWN;
}
