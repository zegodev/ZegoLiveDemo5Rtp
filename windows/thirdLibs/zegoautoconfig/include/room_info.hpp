// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from auto_config.djinni

#pragma once

#include "stream_info.hpp"
#include <string>
#include <utility>
#include <vector>

namespace zego {

struct RoomInfo final {
    std::string room_id;
    std::string room_name;
    std::string anchor_id_name;
    std::string anchor_nick_name;
    std::vector<StreamInfo> stream_info;

    RoomInfo(std::string room_id_,
             std::string room_name_,
             std::string anchor_id_name_,
             std::string anchor_nick_name_,
             std::vector<StreamInfo> stream_info_)
    : room_id(std::move(room_id_))
    , room_name(std::move(room_name_))
    , anchor_id_name(std::move(anchor_id_name_))
    , anchor_nick_name(std::move(anchor_nick_name_))
    , stream_info(std::move(stream_info_))
    {}
};

}  // namespace zego