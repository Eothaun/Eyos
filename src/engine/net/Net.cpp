#include <engine/net/NetFwd.h>
#include <engine/net/Allocator.h>
#include <iostream>

namespace eyos::net {
    void InitializeNetwork()
    {
        auto& alloc{ GetNetworkAllocator() };
        alloc.Init(1024);
        //assertm(enet_initialize() == 0, "An error occurred while initializing ENet.\n");
        
        static auto malloc = [](std::size_t size)->void* {
            std::cout << "malloc(" << size << ")\n";
            auto ptr = GetNetworkAllocator().Allocate(size);
            printf("ptr lives at %p.\n", ptr);
            return ptr;
        };
        static auto free = [](void* ptr) {
            std::cout << "free( ptr )\n";
            printf("ptr lived at %p.\n", ptr);
            return  GetNetworkAllocator().Free(ptr);
        };
        ENetCallbacks callbacks{
            malloc,
            free,
            nullptr
        };
        assertm(enet_initialize_with_callbacks(ENET_VERSION,&callbacks) == 0, "An error occurred while initializing ENet.\n");
        /**/
    }
    void DeinitializeNetwork()
    {
        enet_deinitialize();
    }
}