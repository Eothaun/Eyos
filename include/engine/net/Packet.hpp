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
