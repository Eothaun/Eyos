#include <engine/net/Peer.hpp>
#include <engine/net/Address.hpp>
namespace eyos::net {
///////////////////////////////
/// Peer  implementation   ///
//////////////////////////////

Peer::Peer(ENetPeer* peer)
    : enetPeer { peer }
{
    assertm(peer != nullptr, "Peer is not valid.\n");
}
Peer::Peer(Peer&& peer) noexcept
{
    this->enetPeer = peer.enetPeer;
}

Address Peer::Address()
{
    return { enetPeer->address };
};

bool Peer::IsConnected()
{
    return enetPeer->state == ENetPeerState::ENET_PEER_STATE_CONNECTED;
}

Peer& Peer::operator=(Peer&& peer) noexcept
{
    this->enetPeer = peer.enetPeer;
    return *this;
}
}
