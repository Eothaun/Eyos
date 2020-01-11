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

#include <optional>
namespace eyos::net {
/*
    * \important contains an NONE owning pointer
    */
class EYOS_API Peer {
public:
    Peer(ENetPeer*);
    ~Peer() = default;
    Peer(const Peer&) = delete;
    Peer(Peer&& peer) noexcept;
    Peer& operator=(const Peer&) = delete;
    Peer& operator=(Peer&& peer) noexcept;

public:
    net::Address Address();
    template <typename Data_>
    std::optional<Data_> Data()
    {
        if (enetPeer->data == nullptr)
            return std::nullopt;
        Data_ data {};
        memcpy(&data, &enetPeer->data, sizeof(Data));
        return { data };
    }
    template <typename Data>
    void SetData(Data data)
    {
        memcpy(&data, enetPeer->data, sizeof(Data));
    }
    bool IsConnected();

private:
    ENetPeer* enetPeer { nullptr };
    //friends:
    friend EYOS_API bool SendPacket(const Peer& peer, Packet&& packet);
    friend EYOS_API void Broadcast(const Host& peer, Packet&& packet, std::uint8_t channelID);
    friend class EYOS_API Host;
};
}
