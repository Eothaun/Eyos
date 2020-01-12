#pragma once
///*
//#include <engine/Defines.hpp>
//#pragma warning(push)
//#pragma warning(disable : 6385)
//#pragma warning(disable : 26451)
//#include <enet/enet.h>
//#pragma warning(pop)
//#include <functional>
//#include <iostream>
//#include <memory>
//#include <optional>
//#include <string>
//#include <vector>
//
//namespace eyos::net {
//
//EYOS_API void InitializeNetwork();
//EYOS_API void DeinitializeNetwork();
//
//// Network Lib Wrappers forward:
//class EYOS_API Address;
//class EYOS_API Host;
//class EYOS_API Peer;
//class EYOS_API Packet;
//
//using Event = ENetEvent;
//
////Pointers:
//using Host_ptr = std::unique_ptr<Host>;
//// Network Action
//class EYOS_API NetEventHandler;
////Free functions
//[[nodiscard]] EYOS_API Address CreateAddress(std::uint16_t port, std::uint32_t host = ENET_HOST_ANY);
//[[nodiscard]] EYOS_API Address CreateAddress(std::uint16_t port, const std::string& hostName);
//[[nodiscard]] EYOS_API Host_ptr CreateHost(const Address& address,
//    size_t peerCount = 32,
//    size_t channelLimit = 2,
//    std::uint32_t incomingBandwidth = 0,
//    std::uint32_t outgoingBandwidth = 0);
//[[nodiscard]] EYOS_API Host_ptr CreateHost(
//    size_t peerCount,
//    size_t channelLimit,
//    std::uint32_t incomingBandwidth,
//    std::uint32_t outgoingBandwidth);
//
//[[nodiscard]] EYOS_API Host_ptr CreateServer(
//    std::uint16_t port,
//    size_t peerCount = 32,
//    size_t channelLimit = 2,
//    std::uint32_t incomingBandwidth = 0,
//    std::uint32_t outgoingBandwidth = 0);
//
//[[nodiscard]] EYOS_API Host_ptr CreateClient(
//    size_t peerCount = 1,
//    size_t channelLimit = 2,
//    std::uint32_t incomingBandwidth = 0,
//    std::uint32_t outgoingBandwidth = 0);
//
//EYOS_API bool SendPacket(const Peer& peer, Packet&& packet);
//EYOS_API void Broadcast(const Host& peer, Packet&& packet, std::uint8_t channelID);
//
//template <typename PacketHeaderType>
//[[nodiscard]] Packet CreateEmptyPacket(const PacketHeaderType packetType, std::size_t length)
//{
//    static_assert(std::is_enum_v<PacketHeaderType>, "Is not an Enum!");
//    auto size{ length + sizeof(PacketHeaderType) };
//    std::vector<std::byte> buffer{ size };
//    memcpy(buffer.data(), &packetType, sizeof(PacketHeaderType));
//    auto* enetPacket{ enet_packet_create(buffer.data(), size, ENET_PACKET_FLAG_RELIABLE) };
//    assertm(enetPacket != nullptr, "Could not create a packet");
//    return { enetPacket };
//};
//
//template <typename PacketHeaderType, typename Data>
//[[nodiscard]] Packet CreatePacket(const PacketHeaderType packetType, const Data& data, std::size_t length)
//{
//    static_assert(std::is_enum_v<PacketHeaderType>, "Is not an Enum!");
//    auto size { length + sizeof(PacketHeaderType) };
//    std::vector<std::byte> buffer { size };
//    memcpy(buffer.data(), &packetType, sizeof(PacketHeaderType));
//    memcpy(&buffer[sizeof(PacketHeaderType)], &data, length);
//    auto* enetPacket { enet_packet_create(buffer.data(), size, ENET_PACKET_FLAG_RELIABLE) };
//    assertm(enetPacket != nullptr, "Could not create a packet");
//    return { enetPacket };
//};
//
//template <typename Data>
//[[nodiscard]] Packet&& AppendToPacket(Packet&& packet, const Data& data, std::size_t length)
//{
//    enet_packet_resize(packet.enetPacket, length);
//    memcpy(&packet.enetPacket->data[packet.enetPacket->dataLength], &data, length);
//    return std::move(packet);
//}
//
//template <typename Data>
//[[nodiscard]] Packet&& AppendToPacket(Packet&& packet, Data&& data, std::size_t length)
//{
//    enet_packet_resize(packet.enetPacket, length);
//    memcpy(&packet.enetPacket->data[packet.enetPacket->dataLength], &data, length);
//    return std::move(packet);
//}
//
////class defentions:
///*
//    ports 49152 to 65535 are known as dynamic ports. These are never assigned by IANA
//    and are fair game for any process to use. If a process attempts to bind to a dynamic port and
//    finds that it is in use, it should handle that gracefully by attempting to bind to other dynamic
//    ports until an available one is found. As a good Internet citizen, you should use only dynamic
//    ports while building your multiplayer games, and then register with IANA for a user port
//    assignment if necessary. - Page 40
// */
//class EYOS_API Address {
//public:
//    Address(ENetAddress*);
//    Address(const ENetAddress&);
//    Address(std::uint16_t port = 49200, std::uint32_t host = ENET_HOST_ANY);
//    Address(const std::string& hostName, std::uint16_t port);
//    Address(const Address&) = default;
//    Address(Address&&) = default;
//    Address& operator=(const Address&) = default;
//    Address& operator=(Address&&) = default;
//
//public:
//    bool ResolveHostName(const std::string& hostname);
//    bool ResolveHostIP(const std::string& ipaddress);
//
//    [[nodiscard]] std::string HostStr(std::size_t hostLength = 64);
//    [[nodiscard]] std::uint32_t Host();
//    [[nodiscard]] std::string Ip4();
//    [[nodiscard]] std::string Ip6();
//    [[nodiscard]] std::string Ip(std::size_t length);
//    [[nodiscard]] std::uint16_t Port();
//
//private:
//    ENetAddress enetAddress { ENET_HOST_ANY, 49200 };
//    //friends:
//    friend EYOS_API class Host;
//};
///*
//* \important contains an NONE owning pointer
//*/
//class EYOS_API Peer {
//public:
//    Peer(ENetPeer*);
//    ~Peer() = default;
//    Peer(const Peer&) = delete;
//    Peer(Peer&& peer) noexcept;
//    Peer& operator=(const Peer&) = delete;
//    Peer& operator=(Peer&& peer) noexcept;
//
//public:
//    Address Address();
//    template <typename Data>
//    std::optional<Data> Data()
//    {
//        if (enetPeer->data == nullptr)
//            return std::nullopt;
//        Data data {};
//        memcpy(&data, &enetPeer->data, sizeof(Data));
//        return { data };
//    }
//    template <typename Data>
//    void SetData(Data data)
//    {
//        memcpy(&data, enetPeer->data, sizeof(Data));
//    }
//    bool IsConnected();
//
//private:
//    ENetPeer* enetPeer { nullptr };
//    //friends:
//    friend EYOS_API bool SendPacket(const Peer& peer, Packet&& packet);
//    friend EYOS_API void Broadcast(const Host& peer, Packet&& packet, std::uint8_t channelID);
//    friend EYOS_API Host;
//};
//
//class EYOS_API Host {
//public:
//    Host(std::size_t peerCount,
//        std::size_t channelLimit,
//        std::uint32_t incomingBandwidth,
//        std::uint32_t outgoingBandwidth);
//
//    Host(std::size_t peerCount,
//        std::size_t channelLimit,
//        std::uint32_t incomingBandwidth,
//        std::uint32_t outgoingBandwidth,
//        const Address& address);
//
//    Host(std::size_t peerCount,
//        std::size_t channelLimit,
//        std::uint32_t incomingBandwidth,
//        std::uint32_t outgoingBandwidth,
//        Address&& address);
//
//    Host(const Host&) = delete;
//    Host(Host&& host) = default;
//    Host& operator=(const Host& other) = delete;
//    Host& operator=(Host&& other) = default;
//    ~Host();
//
//public:
//    Peer Connect(const Address& address, std::size_t channelCount, std::uint32_t data) const noexcept;
//    std::size_t CountConnectedPeers() const noexcept;
//    ;
//    std::size_t Host::CountPeers(ENetPeerState state) const noexcept;
//    std::vector<Peer> Host::GetConnectedPeers() const noexcept;
//    Peer GetPeer(std::size_t peerIdx);
//    bool IsPeerValid(const Peer& peer);
//
//private:
//    ENetHost* enetHost { nullptr };
//    friend EYOS_API void Broadcast(const Host& peer, Packet&& packet, std::uint8_t channelID);
//    friend class EYOS_API NetEventHandler;
//};
//
//class EYOS_API Packet {
//public:
//    Packet(ENetPacket* packet)
//        : enetPacket { packet }
//    {
//    }
//    Packet(const Packet&) = delete;
//    Packet(Packet&&) = default;
//    Packet& operator=(const Packet&) = delete;
//    Packet& operator=(Packet&&) = default;
//    ~Packet() = default;
//    /*
//    * \remark: Should only be used in case it has not been send
//    */
//    void Destroy();
//    template <typename PacketHeaderType>
//    std::string&& Data(std::string&& data)
//    {
//        static_assert(!std::is_enum_v<PacketHeaderType>, "Is not an Enum!");
//        auto size { enetPacket->dataLength - sizeof(PacketHeaderType) };
//        data.resize(size);
//        memcpy(data.data(), &enetPacket->data[sizeof(PacketHeaderType)], size);
//        return std::move(data);
//    }
//    template <typename PacketHeaderType, typename Data>
//    Data&& Data(Data&& data)
//    {
//        static_assert(std::is_enum_v<PacketHeaderType>, "Is not an Enum!");
//        memcpy(&data, &enetPacket->data[sizeof(PacketHeaderType)], enetPacket->dataLength - sizeof(PacketHeaderType));
//        return std::move(data);
//    }
//    template <typename PacketHeaderType>
//    PacketHeaderType Type()
//    {
//        static_assert(std::is_enum_v<PacketHeaderType>, "Is not an Enum!");
//        PacketHeaderType type {};
//        memcpy(&type, enetPacket->data, sizeof(PacketHeaderType));
//        return type;
//    }
//
//private:
//    ENetPacket* enetPacket {};
//    template <typename Data>
//    friend Packet&& AppendToPacket(Packet&& packet, const Data&, std::size_t length);
//    template <typename Data>
//    friend Packet&& AppendToPacket(Packet&& packet, Data&&, std::size_t length);
//    friend EYOS_API bool SendPacket(const Peer&, Packet&& packet);
//    friend EYOS_API void Broadcast(const Host& peer, Packet&& packet, std::uint8_t channelID);
//};
//
//enum class NetEvents {
//    None,
//    Connect,
//    Disconnect,
//    Receive
//};
//
//// Network Handler:
//class EYOS_API NetEventHandler {
//public:
//    NetEventHandler() = default;
//    ~NetEventHandler() = default;
//private:
//    using PacketCallback = void(Packet&& packet, [[maybe_unused]] std::uint32_t eventData);
//    using PacketCallback_ = void(*)(Packet&& packet, [[maybe_unused]] std::uint32_t eventData);
//    using ConnectCallback = void(Peer&& who, [[maybe_unused]] std::uint32_t eventData);
//    using ConnectCallback_ = void(*)(Peer&& who, [[maybe_unused]] std::uint32_t eventData);
//    template <typename Member>
//    using MemberPacketCallback = void (Member::*)(Packet&& packet, [[maybe_unused]] std::uint32_t eventData);
//    template <typename Member>
//    using MemberConnectCallback = void (Member::*)(Peer&& who, [[maybe_unused]] std::uint32_t eventData);
//public:
//    template <typename CallbackType>
//    bool AddCallback(const Host_ptr& host, NetEvents netEvent, std::function<CallbackType>&& callback)
//    {
//        auto hostIdx{ GetHostIdx(*host) };
//        if constexpr (std::is_same_v<CallbackType, ConnectCallback>) {
//            if (netEvent == NetEvents::Connect) {
//                onConnect[hostIdx].push_back(std::move(callback));
//            }
//            else {
//                onDisconnect[hostIdx].push_back(std::move(callback));
//            }
//            return true;
//        }
//        if constexpr (std::is_same_v<CallbackType, PacketCallback>) {
//            onReceive[hostIdx].push_back(std::move(callback));
//            return true;
//        }
//        return false;
//    }
//    template <typename This,typename CallbackType>
//    bool AddCallback(const Host_ptr& host, NetEvents netEvent, This* this_ptr, CallbackType&& callback)
//    {
//        return AddCallback(*host, netEvent, this_ptr,std::forward<CallbackType>(callback));
//    }
//    template <typename CallbackType>
//    bool AddCallback(const Host_ptr& host, NetEvents netEvent, CallbackType&& callback)
//    {
//        return AddCallback(*host, netEvent, std::forward<CallbackType>(callback));
//    }
//    template <typename CallbackType>
//    bool AddCallback(const Host& host, NetEvents netEvent, CallbackType&& callback)
//    {
//        auto hostIdx{ GetHostIdx(host) };
//        if constexpr (std::is_same_v<CallbackType, ConnectCallback_>) {
//            std::function<ConnectCallback> func{ std::forward<CallbackType>(callback) };
//            if (netEvent == NetEvents::Connect){
//                onConnect[hostIdx].push_back(std::move(func));
//            }
//            else {
//                onDisconnect[hostIdx].push_back(std::move(func));
//            }
//            return true;
//        }
//        if constexpr (std::is_same_v<CallbackType, PacketCallback_>) {
//            std::function<PacketCallback> func{ std::forward<CallbackType>(callback) };
//            onReceive[hostIdx].push_back(std::move(func));
//            return true;
//        }
//        return false;
//    };
//    template <typename This,typename CallbackType>
//    bool AddCallback(const Host& host, NetEvents netEvent, This* this_ptr, CallbackType&& callback)
//    {
//        auto hostIdx{ GetHostIdx(host) };
//        if constexpr (std::is_same_v<CallbackType, MemberConnectCallback<This>>) {
//            std::function<ConnectCallback> func{ [obj_ptr = this_ptr,func = std::forward<CallbackType>(callback)] (Peer&& who, [[maybe_unused]] std::uint32_t eventData) {
//                std::invoke(func,obj_ptr,std::forward<Peer>(who), eventData);
//            } };
//            if (netEvent == NetEvents::Connect) {
//                onConnect[hostIdx].push_back(std::move(func));
//            }
//            else {
//                onDisconnect[hostIdx].push_back(std::move(func));
//            }
//            return true;
//        }
//        if constexpr (std::is_same_v<CallbackType, MemberPacketCallback<This>>) {
//            std::function<PacketCallback> func{ [obj_ptr = this_ptr,func = std::forward<CallbackType>(callback)] (Packet&& who, [[maybe_unused]] std::uint32_t eventData) {
//                std::invoke(func,obj_ptr,std::forward<Peer>(who), eventData);
//            } };
//            onReceive[hostIdx].push_back(std::move(func));
//            return true;
//        }
//        return false;
//    };
//    void Poll(const Host& host, std::uint32_t timeout = 5000);
//    void Poll(const Host_ptr& host, std::uint32_t timeout = 5000);
//private:
//    std::size_t GetHostIdx(const Host&);
//private:
//#pragma warning(push)
//#pragma warning(disable : 4251)
//    std::unordered_map<std::size_t, std::size_t> hosts {};
//    std::vector<std::vector<std::function<ConnectCallback>>> onConnect {};
//    std::vector<std::vector<std::function<ConnectCallback>>> onDisconnect {};
//    std::vector<std::vector<std::function<PacketCallback>>> onReceive {};
//#pragma warning(push)
//    std::hash<const Host*> hashFunc {};
//};
//
//} // namespace eyos
