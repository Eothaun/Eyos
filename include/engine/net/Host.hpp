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

#include <vector>
namespace eyos::net {

class EYOS_API Host {
public:
    Host(std::size_t peerCount,
        std::size_t channelLimit,
        std::uint32_t incomingBandwidth,
        std::uint32_t outgoingBandwidth);

    Host(std::size_t peerCount,
        std::size_t channelLimit,
        std::uint32_t incomingBandwidth,
        std::uint32_t outgoingBandwidth,
        const Address& address);

    Host(std::size_t peerCount,
        std::size_t channelLimit,
        std::uint32_t incomingBandwidth,
        std::uint32_t outgoingBandwidth,
        Address&& address);

    Host(const Host&) = delete;
    Host(Host&& host) = default;
    Host& operator=(const Host& other) = delete;
    Host& operator=(Host&& other) = default;
    ~Host();

public:
    Peer Connect(const Address& address, std::size_t channelCount, std::uint32_t data) const noexcept;
    std::size_t CountConnectedPeers() const noexcept;
    std::size_t Host::CountPeers(ENetPeerState state) const noexcept;
    std::vector<class Peer> Host::GetConnectedPeers() const noexcept;
    Peer GetPeer(std::size_t peerIdx);
    bool IsPeerValid(const Peer& peer);

private:
    ENetHost* enetHost { nullptr };
    friend EYOS_API void Broadcast(const Host& peer, Packet&& packet, std::uint8_t channelID);
    friend class EYOS_API NetEventHandler;
};
}
