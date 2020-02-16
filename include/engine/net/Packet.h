#pragma once
/*
Eyos Source Code License v1.0
Copyright (c) 2019-2020 Simon Renger, Maiko Steeman, Marjolein Kaal, Hannes Vernooij
Last updated on February 16th, 2020.
*/
#include "NetFwd.h"
#include <string>
#include <cstring>
namespace eyos::net {

class EYOS_API Packet {
public:
    Packet(ENetPacket* packet)
        : enetPacket { packet }
    {
    }
    Packet(const Packet&) = delete;
    Packet(Packet&&) = default;
    Packet& operator=(const Packet&) = delete;
    Packet& operator=(Packet&&) = default;
    ~Packet() = default;
    /*
    * \remark: Should only be used in case it has not been send
    */
    void Destroy();
    template <typename PacketHeaderType>
    PacketHeaderType Type()
    {
        static_assert(std::is_enum_v<PacketHeaderType>, "Is not an Enum!");
        PacketHeaderType type {};
        memcpy(&type, enetPacket->data, sizeof(PacketHeaderType));
        return type;
    }

private:
    ENetPacket* enetPacket {};
    friend EYOS_API bool SendPacket(const net::Peer& peer, net::Packet&& packet);
    friend EYOS_API void Broadcast(const net::Host& peer, net::Packet&& packet, std::uint8_t channelID);
};
}
