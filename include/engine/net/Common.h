#pragma once
/*
Eyos Source Code License v1.0
Copyright (c) 2019-2020 Simon Renger, Maiko Steeman, Marjolein Kaal, Hannes Vernooij
Last updated on February 16th, 2020.
*/
#include "NetFwd.h"
#include "Packet.h"
#include <string>
#include <vector>
#include <cstddef>
namespace eyos::net {
//Free functions
[[nodiscard]] EYOS_API net::Address CreateAddress(std::uint16_t port, std::uint32_t host = ENET_HOST_ANY);
[[nodiscard]] EYOS_API net::Address CreateAddress(std::uint16_t port, const std::string& hostName);
[[nodiscard]] EYOS_API Host_ptr CreateHost(const net::Address& address,
    size_t peerCount = 32,
    size_t channelLimit = 2,
    std::uint32_t incomingBandwidth = 0,
    std::uint32_t outgoingBandwidth = 0);
[[nodiscard]] EYOS_API Host_ptr CreateHost(
    size_t peerCount,
    size_t channelLimit,
    std::uint32_t incomingBandwidth,
    std::uint32_t outgoingBandwidth);

[[nodiscard]] EYOS_API Host_ptr CreateServer(
    std::uint16_t port,
    size_t peerCount = 32,
    size_t channelLimit = 2,
    std::uint32_t incomingBandwidth = 0,
    std::uint32_t outgoingBandwidth = 0);

[[nodiscard]] EYOS_API Host_ptr CreateClient(
    size_t peerCount = 1,
    size_t channelLimit = 2,
    std::uint32_t incomingBandwidth = 0,
    std::uint32_t outgoingBandwidth = 0);

EYOS_API bool SendPacket(const net::Peer& peer, net::Packet&& packet);
EYOS_API void Broadcast(const net::Host& peer, net::Packet&& packet, std::uint8_t channelID);

template <typename PacketHeaderType>
[[nodiscard]] net::Packet CreateEmptyPacket(const PacketHeaderType packetType)
{
    static_assert(std::is_enum_v<PacketHeaderType>, "Is not an Enum!");
    auto size {sizeof(PacketHeaderType) };
    std::vector<std::byte> buffer { size };
    memcpy(buffer.data(), &packetType, sizeof(PacketHeaderType));
    auto* enetPacket { enet_packet_create(buffer.data(), size, ENET_PACKET_FLAG_RELIABLE) };
    assertm(enetPacket != nullptr, "Could not create a packet");
    return { enetPacket };
};


}