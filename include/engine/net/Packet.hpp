#pragma once
/*
Eyos Source Code License v1.0
Copyright (c) 2019-2020 Simon Renger, Maiko Steeman, Marjolein Kaal, Hannes Vernooij
Last updated on February 16th, 2020.
*/
#include "NetFwd.hpp"
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
    std::string&& Data(std::string&& data)
    {
        static_assert(!std::is_enum_v<PacketHeaderType>, "Is not an Enum!");
        auto size { enetPacket->dataLength - sizeof(PacketHeaderType) };
        data.resize(size);
        memcpy(data.data(), &enetPacket->data[sizeof(PacketHeaderType)], size);
        return std::move(data);
    }
    template <typename PacketHeaderType, typename Data_>
    Data_&& Data(Data_&& data)
    {
        static_assert(std::is_enum_v<PacketHeaderType>, "Is not an Enum!");
        memcpy(&data, &enetPacket->data[sizeof(PacketHeaderType)], enetPacket->dataLength - sizeof(PacketHeaderType));
        return std::move(data);
    }
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
    template <typename Data>
    friend Packet&& AppendToPacket(Packet&& packet, const Data&, std::size_t length);
    template <typename Data>
    friend Packet&& AppendToPacket(Packet&& packet, Data&&, std::size_t length);
    friend EYOS_API bool SendPacket(const Peer&, Packet&& packet);
    friend EYOS_API void Broadcast(const Host& peer, Packet&& packet, std::uint8_t channelID);
};
}
