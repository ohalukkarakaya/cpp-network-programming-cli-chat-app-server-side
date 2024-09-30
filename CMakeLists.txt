cmake_minimum_required(VERSION 3.27)
project(cpp_network_programming_cli_chat_app_server_side)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp_network_programming_cli_chat_app_server_side main.cpp
        Models/room_member/room_member.h
        Models/room_member/room_member.cpp
        Models/room/room.h
        Models/room/room.cpp
        src/send_to_ip/send_to_ip.h
        src/send_to_ip/send_to_ip.cpp)
