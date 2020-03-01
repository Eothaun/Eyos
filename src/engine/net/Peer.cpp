#include <engine/net/Peer.h>
#include <engine/net/Address.h>
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

[[nodiscard]] Address Peer::Address()
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
