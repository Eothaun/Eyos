#include <engine/net/NetFwd.hpp>

namespace eyos::net {
    void InitializeNetwork()
    {
        assertm(enet_initialize() == 0, "An error occurred while initializing ENet.\n");
    }
    void DeinitializeNetwork()
    {
        enet_deinitialize();
    }
}