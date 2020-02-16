#pragma once
/*
Eyos Source Code License v1.0
Copyright (c) 2019-2020 Simon Renger, Maiko Steeman, Marjolein Kaal, Hannes Vernooij
Last updated on February 16th, 2020.
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
    [[nodiscard]] net::Address Address();
    template <typename Data_>
    [[nodiscard]] std::optional<Data_> Data()
    {
        if (enetPeer->data == nullptr)
            return std::nullopt;
        Data_ data {};
        memcpy(&data, &enetPeer->data, sizeof(Data_));
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
