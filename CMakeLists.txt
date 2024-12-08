cmake_minimum_required(VERSION 3.27)
project(cpp_network_programming_cli_chat_app_server_side)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        cpp_network_programming_cli_chat_app_server_side main.cpp
        
        Models/room_member/room_member.h
        Models/room_member/room_member.cpp

        Models/room/room.h
        Models/room/room.cpp

        src/send_to_ip/send_to_ip.h
        src/send_to_ip/send_to_ip.cpp

        src/handle_client/handle_client.cpp
        src/handle_client/handle_client.h

        src/process_request/process_request.h
        src/process_request/process_request.cpp

        include/global_variables.h

        Models/request_type_enum/request_type_enum.h
        Models/request_type_enum/request_type_enum.cpp

        src/scokets_helper/sockets_helper.h
        src/scokets_helper/sockets_helper.cpp

        src/parse_request/parse_request.h
        src/parse_request/parse_request.cpp

        Models/request_data/request_data.h
        Models/request_data/request_data.cpp

        src/join_room/join_room.h
        src/join_room/join_room.cpp

        src/update_ip/update_ip.h
        src/update_ip/update_ip.cpp

        src/leave_room/leave_room.h
        src/leave_room/leave_room.cpp
        
        src/get_rooms/get_rooms.h
        src/get_rooms/get_rooms.cpp

        src/get_ip_adress/get_ip_adress.cpp
        src/get_ip_adress/get_ip_adress.h

        Models/room_manager/room_manager.h
        Models/room_manager/room_manager.cpp
)
