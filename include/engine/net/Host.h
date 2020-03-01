#pragma once
/*
Eyos Source Code License v1.0
Copyright (c) 2019-2020 Simon Renger, Maiko Steeman, Marjolein Kaal, Hannes Vernooij
Last updated on February 16th, 2020.
*/
#include "NetFwd.h"

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
    [[nodiscard]] std::size_t CountConnectedPeers() const noexcept;
    [[nodiscard]] std::size_t CountPeers(ENetPeerState state) const noexcept;
    [[nodiscard]] auto GetConnectedPeers() const noexcept;
    [[nodiscard]]  Peer GetPeer(std::size_t peerIdx);
    bool IsPeerValid(const Peer& peer);

private:
    ENetHost* enetHost { nullptr };
    friend EYOS_API void Broadcast(const Host& peer, Packet&& packet, std::uint8_t channelID);
    friend class EYOS_API NetEventHandler;
};
}
