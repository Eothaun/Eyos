#pragma once
/*
Eyos Source Code License v1.0
Copyright (c) 2019-2020 Simon Renger, Maiko Steeman, Marjolein Kaal, Hannes Vernooij
Last updated on February 16th, 2020.
*/
#include "NetFwd.h"
#include "engine/Defines.h"
#include <string>
#include <cstring>

namespace eyos::net {

class EYOS_API Packet {
public:
    Packet(ENetPacket* packet, std::size_t typeSize = sizeof(unsigned int))
        : enetPacket{ packet }, typeSize{ typeSize }
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
        assertm(typeSize == sizeof(PacketHeaderType), "Saved size of type is different then actualy size!");
        PacketHeaderType type {};
        memcpy(&type, enetPacket->data, sizeof(PacketHeaderType));
        return type;
    }
    std::size_t Size() const {return enetPacket->dataLength;};
private:
    ENetPacket* enetPacket {};
    std::size_t typeSize{};
    void * Data(std::size_t offset = 0) const {return &enetPacket->data[offset];};
    friend EYOS_API bool SendPacket(const net::Peer& peer, net::Packet&& packet);
    friend EYOS_API void Broadcast(const net::Host& peer, net::Packet&& packet, std::uint8_t channelID);
    template <typename Data>
    friend  Packet&& AppendToPacket(Packet&& packet, Data&& data);
    template <typename Data>
    friend Packet&& AppendToPacket(Packet&& packet, Data&& data, std::size_t length);
    template <typename Data>
    friend  Packet&& AppendToPacket(Packet&& packet, Data& data);
    template <typename Data>
    friend  Packet&& AppendToPacket(Packet&& packet, const Data& data);
    template <typename Data>
    friend  Packet&& AppendToPacket(Packet&& packet, const Data& data, std::size_t length);
    template <typename PacketHeaderType>
    friend Packet StreamToPacket(const PacketHeaderType packetType, InputStream&& stream);
    friend  class EYOS_API InputStream;
    friend  class EYOS_API  OutputStream;
};
}
