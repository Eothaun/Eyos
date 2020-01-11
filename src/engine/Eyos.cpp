//#pragma warning(disable : 26812)
//// our own implementation:
//#include <engine/Eyos.hpp>
//
//// third party libs:
//#include <glm/glm.hpp>
//
//// include std
//#include <algorithm>
//#include <iostream>
//
//namespace eyos::net {
//
//void InitializeNetwork()
//{
//    assertm(enet_initialize() == 0, "An error occurred while initializing ENet.\n");
//}
//void DeinitializeNetwork()
//{
//    enet_deinitialize();
//}
//// Free function implementation
//[[nodiscard]] Address CreateAddress(std::uint16_t port, std::uint32_t host)
//{
//    return { port, host };
//};
//[[nodiscard]] Address CreateAddress(std::uint16_t port, const std::string& hostName)
//{
//    return { hostName, port };
//};
//[[nodiscard]] EYOS_API Host_ptr CreateHost(
//    size_t peerCount,
//    size_t channelLimit,
//    std::uint32_t incomingBandwidth,
//    std::uint32_t outgoingBandwidth)
//{
//    return std::make_unique<Host>(peerCount, channelLimit, incomingBandwidth, outgoingBandwidth);
//};
//[[nodiscard]] Host_ptr CreateHost(const Address& address,
//    size_t peerCount,
//    size_t channelLimit,
//    std::uint32_t incomingBandwidth,
//    std::uint32_t outgoingBandwidth)
//{
//    return std::make_unique<Host>(peerCount, channelLimit, incomingBandwidth, outgoingBandwidth, address);
//};
//[[nodiscard]] Host_ptr CreateServer(
//    std::uint16_t port,
//    size_t peerCount,
//    size_t channelLimit,
//    std::uint32_t incomingBandwidth,
//    std::uint32_t outgoingBandwidth)
//{
//    auto address { CreateAddress(port, "127.0.0.1") };
//    return std::move(CreateHost(address, peerCount, channelLimit, incomingBandwidth, outgoingBandwidth));
//};
//
//[[nodiscard]] Host_ptr CreateClient(
//    size_t peerCount,
//    size_t channelLimit,
//    std::uint32_t incomingBandwidth,
//    std::uint32_t outgoingBandwidth)
//{
//    return std::move(CreateHost(peerCount, channelLimit, incomingBandwidth, outgoingBandwidth));
//};
//
//bool SendPacket(const Peer& peer, Packet&& packet)
//{
//    return 0 == enet_peer_send(peer.enetPeer, 0, packet.enetPacket);
//}
//
//void Broadcast(const Host& peer, Packet&& packet, std::uint8_t channelID)
//{
//    enet_host_broadcast(peer.enetHost, channelID, packet.enetPacket);
//}
//
/////////////////////////////////
///// Address implementation ///
////////////////////////////////
//
//Address::Address(ENetAddress* address)
//    : enetAddress { *address } {};
//Address::Address(const ENetAddress& address)
//    : enetAddress { address } {};
//Address::Address(const std::string& hostName, std::uint16_t port)
//{
//    ResolveHostName(hostName);
//    enetAddress.port = port;
//};
//Address::Address(std::uint16_t port, std::uint32_t host)
//    : enetAddress { host, port } {};
//
//bool Address::ResolveHostIP(const std::string& ipaddress)
//{
//    auto status { enet_address_set_host_ip(&enetAddress, ipaddress.c_str()) };
//    assertm(status == 0, "Could not resolve the ipaddress");
//    return status == 0;
//}
//bool Address::ResolveHostName(const std::string& hostname)
//{
//    auto status { enet_address_set_host(&enetAddress, hostname.c_str()) };
//    assertm(status == 0, "Could not resolve the ipaddress");
//    return status == 0;
//}
//
//std::string Address::HostStr(std::size_t length)
//{
//    std::string host {};
//    host.reserve(length);
//    assertm(enet_address_get_host(&enetAddress, host.data(), length) == 0, "Cannot get Host");
//    return host;
//}
//std::uint32_t Address::Host() { return enetAddress.host; }
//std::string Address::Ip(std::size_t length)
//{
//    std::string ip {};
//    ip.reserve(length);
//    assertm(enet_address_get_host_ip(&enetAddress, ip.data(), ip.size()), "Cannot get ipaddress");
//    return ip;
//}
//std::string Address::Ip6()
//{
//    return std::move(Ip(71));
//}
//std::string Address::Ip4()
//{
//    return std::move(Ip(35));
//}
//std::uint16_t Address::Port() { return enetAddress.port; }
//
/////////////////////////////////
///// Peer  implementation   ///
////////////////////////////////
//
//Peer::Peer(ENetPeer* peer)
//    : enetPeer { peer }
//{
//    assertm(peer != nullptr, "Peer is not valid.\n");
//}
//Peer::Peer(Peer&& peer) noexcept
//{
//    this->enetPeer = peer.enetPeer;
//}
//
//Address Peer::Address()
//{
//    return { enetPeer->address };
//};
//
//bool Peer::IsConnected()
//{
//    return enetPeer->state == ENetPeerState::ENET_PEER_STATE_CONNECTED;
//}
//
//Peer& Peer::operator=(Peer&& peer) noexcept
//{
//    this->enetPeer = peer.enetPeer;
//    return *this;
//}
//
/////////////////////////////////
///// Host  implementation   ///
////////////////////////////////
//
//Host::Host(std::size_t peerCount,
//    std::size_t channelLimit,
//    std::uint32_t incomingBandwidth,
//    std::uint32_t outgoingBandwidth)
//{
//    auto address { Address {} };
//    enetHost = enet_host_create(&address.enetAddress, peerCount, channelLimit, incomingBandwidth, outgoingBandwidth);
//    assertm(enetHost, "Failed creating host");
//}
//Host::Host(std::size_t peerCount,
//    std::size_t channelLimit,
//    std::uint32_t incomingBandwidth,
//    std::uint32_t outgoingBandwidth,
//    const Address& address)
//{
//    enetHost = enet_host_create(&address.enetAddress, peerCount, channelLimit, incomingBandwidth, outgoingBandwidth);
//    assertm(enetHost, "Failed creating host");
//}
//Host::Host(std::size_t peerCount,
//    std::size_t channelLimit,
//    std::uint32_t incomingBandwidth,
//    std::uint32_t outgoingBandwidth,
//    Address&& address)
//{
//    enetHost = enet_host_create(&address.enetAddress, peerCount, channelLimit, incomingBandwidth, outgoingBandwidth);
//    assertm(enetHost, "Failed creating host");
//}
//
//Peer Host::Connect(const Address& address, std::size_t channelCount, std::uint32_t data) const noexcept
//{
//    auto* peer_ptr { enet_host_connect(enetHost, &address.enetAddress, channelCount, data) };
//    assertm(peer_ptr != nullptr, "No available peers for initiating an ENet connection.");
//    return { peer_ptr };
//}
//std::size_t Host::CountConnectedPeers() const noexcept
//{
//    return CountPeers(ENetPeerState::ENET_PEER_STATE_CONNECTED);
//}
//std::size_t Host::CountPeers(ENetPeerState state) const noexcept
//{
//    auto count { 0 };
//    for (auto i { 0 }; i < enetHost->peerCount; ++i) {
//        if (enetHost->peers[i].state == state) {
//            ++count;
//        }
//    }
//    return count;
//};
//
//std::vector<Peer> Host::GetConnectedPeers() const noexcept
//{
//    std::vector<Peer> result {};
//    result.reserve(enetHost->peerCount);
//    for (auto i { 0 }; i < enetHost->peerCount; ++i) {
//        if (enetHost->peers[i].state == ENetPeerState::ENET_PEER_STATE_CONNECTED) {
//            result.emplace_back<Peer>({ &enetHost->peers[i] });
//        }
//    }
//    return result;
//}
//Peer Host::GetPeer(std::size_t peerIdx)
//{
//    assertm(peerIdx < enetHost->peerCount, "Could not find peer in peer register");
//    return { &enetHost->peers[peerIdx] };
//}
//bool Host::IsPeerValid(const Peer& peer)
//{
//    return peer.enetPeer->host == enetHost;
//}
//
//Host::~Host()
//{
//    enet_host_destroy(enetHost);
//}
//
///////////////////////////////////
///// Packet  implementation   ///
/////////////////////////////////
//
//void Packet::Destroy()
//{
//    enet_packet_destroy(enetPacket);
//}
//
////////////////////////////////////////
///// NetEventHandler implementation ///
///////////////////////////////////////
//std::size_t NetEventHandler::GetHostIdx(const Host& host)
//{
//    auto hashVal { hashFunc(&host) };
//    auto itr { std::find_if(hosts.begin(), hosts.end(), [hashVal](auto const& hash) {
//        return hash.first == hashVal;
//    }) };
//    if (itr == std::end(hosts)) {
//        onConnect.push_back({});
//        onDisconnect.push_back({});
//        onReceive.push_back({});
//        hosts.insert({ hashVal, onConnect.size() - 1 });
//        return onConnect.size() - 1;
//    }
//    return itr->second;
//}
//void NetEventHandler::Poll(const Host_ptr& host, std::uint32_t timeout)
//{
//    Poll(*host, timeout);
//}
//void NetEventHandler::Poll(const Host& host, std::uint32_t timeout)
//{
//    auto hostIdx{ GetHostIdx(host) };
//    auto invoke = [](const auto& callbableContainer,auto idx, auto&&... params) {
//        for (const auto& callable : callbableContainer[idx]) {
//            callable(std::forward<decltype(params)>(params)...);
//        }
//    };
//    net::Event event {};
//    while (enet_host_service(host.enetHost, &event, 5000) > 0) {
//        auto eventType{ static_cast<NetEvents>(event.type) };
//        switch (eventType) {
//        case NetEvents::Connect: {
//            std::cout << "process connect";
//            invoke(onConnect, hostIdx, Peer{ event.peer }, static_cast<std::uint32_t>(event.data));
//        } break;
//        case NetEvents::Disconnect:
//            invoke(onDisconnect, hostIdx, Peer{ event.peer }, static_cast<std::uint32_t>(event.data));
//            break;
//        case NetEvents::Receive:
//            invoke(onReceive, hostIdx, Packet{ event.packet }, static_cast<std::uint32_t>(event.data));
//            break;
//        default:
//            break;
//        }
//    }
//}
//}
//#pragma warning(default : 26812)
