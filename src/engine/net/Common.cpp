#include <engine/net/Common.h>
#include <engine/net/Address.h>
#include <engine/net/Host.h>
#include <engine/net/Peer.h>
#include <engine/net/Packet.h>

namespace eyos::net {
    // Free function implementation
    [[nodiscard]] Address CreateAddress(std::uint16_t port, std::uint32_t host)
    {
        return { port, host };
    };
    [[nodiscard]] Address CreateAddress(std::uint16_t port, const std::string& hostName)
    {
        return { hostName, port };
    };
    [[nodiscard]] EYOS_API Host_ptr CreateHost(
        size_t peerCount,
        size_t channelLimit,
        std::uint32_t incomingBandwidth,
        std::uint32_t outgoingBandwidth)
    {
        return std::make_unique<Host>(peerCount, channelLimit, incomingBandwidth, outgoingBandwidth);
    };
    [[nodiscard]] Host_ptr CreateHost(const Address& address,
        size_t peerCount,
        size_t channelLimit,
        std::uint32_t incomingBandwidth,
        std::uint32_t outgoingBandwidth)
    {
        return std::make_unique<Host>(peerCount, channelLimit, incomingBandwidth, outgoingBandwidth, address);
    };
    [[nodiscard]] Host_ptr CreateServer(
        std::uint16_t port,
        size_t peerCount,
        size_t channelLimit,
        std::uint32_t incomingBandwidth,
        std::uint32_t outgoingBandwidth)
    {
        auto address{ CreateAddress(port, "127.0.0.1") };
        return std::move(CreateHost(address, peerCount, channelLimit, incomingBandwidth, outgoingBandwidth));
    };

    [[nodiscard]] Host_ptr CreateClient(
        size_t peerCount,
        size_t channelLimit,
        std::uint32_t incomingBandwidth,
        std::uint32_t outgoingBandwidth)
    {
        return std::move(CreateHost(peerCount, channelLimit, incomingBandwidth, outgoingBandwidth));
    };

    bool SendPacket(const Peer& peer, Packet&& packet)
    {
        return 0 == enet_peer_send(peer.enetPeer, 0, packet.enetPacket);
    }

    void Broadcast(const Host& peer, Packet&& packet, std::uint8_t channelID)
    {
        enet_host_broadcast(peer.enetHost, channelID, packet.enetPacket);
    }
}