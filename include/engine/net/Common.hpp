#pragma once
/*
MIT License

Copyright (c) 2019-2020 Simon Renger, Maiko Steeman, Marjolein Kaal, Hannes Vernooij

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "NetFwd.hpp"
#include "Packet.hpp"
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
[[nodiscard]] net::Packet CreateEmptyPacket(const PacketHeaderType packetType, std::size_t length)
{
    static_assert(std::is_enum_v<PacketHeaderType>, "Is not an Enum!");
    auto size { length + sizeof(PacketHeaderType) };
    std::vector<std::byte> buffer { size };
    memcpy(buffer.data(), &packetType, sizeof(PacketHeaderType));
    auto* enetPacket { enet_packet_create(buffer.data(), size, ENET_PACKET_FLAG_RELIABLE) };
    assertm(enetPacket != nullptr, "Could not create a packet");
    return { enetPacket };
};

template <typename PacketHeaderType, typename Data>
[[nodiscard]] net::Packet CreatePacket(const PacketHeaderType packetType, const Data& data, std::size_t length)
{
    static_assert(std::is_enum_v<PacketHeaderType>, "Is not an Enum!");
    auto size { length + sizeof(PacketHeaderType) };
    std::vector<std::byte> buffer { size };
    memcpy(buffer.data(), &packetType, sizeof(PacketHeaderType));
    memcpy(&buffer[sizeof(PacketHeaderType)], &data, length);
    auto* enetPacket { enet_packet_create(buffer.data(), size, ENET_PACKET_FLAG_RELIABLE) };
    assertm(enetPacket != nullptr, "Could not create a packet");
    return { enetPacket };
};

template <typename Data>
[[nodiscard]] net::Packet&& AppendToPacket(net::Packet&& packet, const Data& data, std::size_t length)
{
    enet_packet_resize(packet.enetPacket, length);
    memcpy(&packet.enetPacket->data[packet.enetPacket->dataLength], &data, length);
    return std::move(packet);
}

template <typename Data>
[[nodiscard]] net::Packet&& AppendToPacket(net::Packet&& packet, Data&& data, std::size_t length)
{
    enet_packet_resize(packet.enetPacket, length);
    memcpy(&packet.enetPacket->data[packet.enetPacket->dataLength], &data, length);
    return std::move(packet);
}
}
