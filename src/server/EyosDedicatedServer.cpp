#include <engine/net/Net.h>
#include "engine/DebugHelper.h"
#include <iostream>

using namespace eyos;
enum class PacketType {
    Send
};
net::Host_ptr Client() {
    return { net::CreateClient() };
}
net::Host_ptr Server() {
    return { net::CreateServer(1234) };
}
void OnConnect(net::Peer&& who,[[maybe_unused]] std::uint32_t eventData) {
    std::cout << "onConnect() Data: "<< eventData <<"\n";
    const net::Peer who_{ std::move(who)};
    /*
    if (net::SendPacket(who_, net::CreatePacket(PacketType::Send, 42, sizeof(int)))) {
        std::cout << "Maybe Send!\n";
    }*/
}
void OnDisconnect(net::Peer&& who,[[maybe_unused]] std::uint32_t eventData) {
    std::cout << "OnDisconnect()\n";
}
void OnReceive(net::Packet&& packet, [[maybe_unused]] std::uint32_t eventData) {
    std::cout << "OnPacketReceive()\n";
    std::cout << "EventData: " << eventData << '\n';
    int data{};
    //data = packet.Data<PacketType,int>(std::move(data));
    //std::cout << "Data: " << data << '\n';
}

struct Lobby {
    std::uint32_t peerIdx{};
};

struct Lobbies {
    enum class LobbyCommands {
        None,
        Create,
        Join,
        Leave,
        List
    };
    net::Host& host;
    void OnConnect(net::Peer&& who, [[maybe_unused]] std::uint32_t eventData) { std::cout << "member::onConnect() 1 Data: " << eventData << "\n"; };
    void OnDisconnect(net::Peer&& who, [[maybe_unused]] std::uint32_t eventData) { std::cout << "onConnect() 2 Data: " << eventData << "\n"; };
    void OnReceive(net::Packet&& packet, [[maybe_unused]] std::uint32_t eventData) {
        auto packetType{ packet.Type<LobbyCommands>() };
        switch (packetType) {
        case LobbyCommands::Join: {

        }break;
        case LobbyCommands::Create: {
        }break;
        case LobbyCommands::Leave: {
        }break;
        case LobbyCommands::List: {
        }break;
        default:break;
        }
    };
    std::vector<Lobby> lobbies{};
};

int main()
{
    net::InitializeNetwork();
    auto client{ Server() };
    auto address{ net::CreateAddress(1234,"127.0.0.1") };
    Lobbies lobbyServer{ *client };

    //client->Connect(address, 2, 42);
    auto eventHandler{ net::NetEventHandler{} };
    auto f = [](net::Packet&& packet, [[maybe_unused]] std::uint32_t eventData)->void {};
    auto c = [](net::Peer&& who, [[maybe_unused]] std::uint32_t eventData)->void {
        std::cout << "Connected Lambda\n";
    };
    eventHandler.AddCallback(client, net::NetEvents::Connect,&lobbyServer,&Lobbies::OnConnect);
    eventHandler.AddCallback(client, net::NetEvents::Connect, std::function<void(net::Peer && who, [[maybe_unused]] std::uint32_t eventData)>{c});
    eventHandler.AddCallback(client, net::NetEvents::Connect, &OnConnect);
    eventHandler.AddCallback(client, net::NetEvents::Disconnect,&OnDisconnect);
    eventHandler.AddCallback(client, net::NetEvents::Receive, &OnReceive);
    bool run{ true };
    while (run) {
            //updates the client:
            eventHandler.Poll(client);
    }
    net::DeinitializeNetwork();
}