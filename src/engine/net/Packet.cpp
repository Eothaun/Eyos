#include <engine/net/Packet.hpp>

namespace eyos::net {
/////////////////////////////////
/// Packet  implementation   ///
///////////////////////////////

void Packet::Destroy()
{
    enet_packet_destroy(enetPacket);
}

}
