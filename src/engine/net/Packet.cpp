#include <engine/net/Packet.h>

namespace eyos::net {
/////////////////////////////////
/// Packet  implementation   ///
///////////////////////////////

void Packet::Destroy()
{
    enet_packet_destroy(enetPacket);
}

}
