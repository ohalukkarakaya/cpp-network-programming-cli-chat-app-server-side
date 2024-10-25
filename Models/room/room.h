#ifndef ROOM_H
#define ROOM_H

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "../room_member/room_member.h"

#include "../../src/scokets_helper/sockets_helper.h"
#include "../../src/send_to_ip/send_to_ip.h"

class Room {
public:
  Room(std::string id) : roomId(std::move(id)) {}

  void userJoined(const std::string &userId, const std::string &userIp);
  void userLeft(const std::string &userId);
  void updateUserIp(const std::string &userId, const std::string &newIp);
  std::optional<RoomMember> findUser(const std::string &userId);
  [[nodiscard]] const std::string &getRoomId() const;
  [[nodiscard]] const std::vector<RoomMember> &getMembers() const;

private:
  std::string roomId;
  std::vector<RoomMember> members;
};

#endif // ROOM_H
