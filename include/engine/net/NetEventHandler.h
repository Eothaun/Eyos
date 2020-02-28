#pragma once
/*
Eyos Source Code License v1.0
Copyright (c) 2019-2020 Simon Renger, Maiko Steeman, Marjolein Kaal, Hannes Vernooij
Last updated on February 16th, 2020.
*/
#include "NetFwd.h"
#include <functional>

namespace eyos::net {
    enum  class NetEvents {
        None,
        Connect,
        Disconnect,
        Receive
    };

    // Network Handler:
    class EYOS_API NetEventHandler {
    public:
        NetEventHandler() = default;
        ~NetEventHandler() = default;
    private:
        using PacketCallback = void(net::Packet && packet, [[maybe_unused]] std::uint32_t eventData);
        using PacketCallback_ = void(*)(net::Packet && packet, [[maybe_unused]] std::uint32_t eventData);
        using ConnectCallback = void(net::Peer && who, [[maybe_unused]] std::uint32_t eventData);
        using ConnectCallback_ = void(*)(net::Peer && who, [[maybe_unused]] std::uint32_t eventData);
        template <typename Member>
        using MemberPacketCallback = void (Member::*)(net::Packet && packet, [[maybe_unused]] std::uint32_t eventData);
        template <typename Member>
        using MemberConnectCallback = void (Member::*)(net::Peer && who, [[maybe_unused]] std::uint32_t eventData);
    public:
        template <typename CallbackType>
        bool AddCallback(const Host_ptr& host, net::NetEvents netEvent, std::function<CallbackType>&& callback)
        {
            auto hostIdx{ GetHostIdx(*host) };
            if constexpr (std::is_same_v<CallbackType, ConnectCallback>) {
                if (netEvent == net::NetEvents::Connect) {
                    onConnect[hostIdx].push_back(std::move(callback));
                }
                else {
                    onDisconnect[hostIdx].push_back(std::move(callback));
                }
                return true;
            }
            if constexpr (std::is_same_v<CallbackType, PacketCallback>) {
                onReceive[hostIdx].push_back(std::move(callback));
                return true;
            }
            return false;
        }
        template <typename This, typename CallbackType>
        bool AddCallback(const net::Host_ptr& host, net::NetEvents netEvent, This* this_ptr, CallbackType&& callback)
        {
            return AddCallback(*host, netEvent, this_ptr, std::forward<CallbackType>(callback));
        }
        template <typename CallbackType>
        bool AddCallback(const net::Host_ptr& host, net::NetEvents netEvent, CallbackType&& callback)
        {
            return AddCallback(*host, netEvent, std::forward<CallbackType>(callback));
        }
        template <typename CallbackType>
        bool AddCallback(const Host& host, NetEvents netEvent, CallbackType&& callback)
        {
            auto hostIdx{ GetHostIdx(host) };
            if constexpr (std::is_same_v<CallbackType, ConnectCallback_>) {
                std::function<ConnectCallback> func{ std::forward<CallbackType>(callback) };
                if (netEvent == NetEvents::Connect) {
                    onConnect[hostIdx].push_back(std::move(func));
                }
                else {
                    onDisconnect[hostIdx].push_back(std::move(func));
                }
                return true;
            }
            if constexpr (std::is_same_v<CallbackType, PacketCallback_>) {
                std::function<PacketCallback> func{ std::forward<CallbackType>(callback) };
                onReceive[hostIdx].push_back(std::move(func));
                return true;
            }
            return false;
        };
        template <typename This, typename CallbackType>
        bool AddCallback(const net::Host& host, net::NetEvents netEvent, This* this_ptr, CallbackType&& callback)
        {
            auto hostIdx{ GetHostIdx(host) };
            if constexpr (std::is_same_v<CallbackType, MemberConnectCallback<This>>) {
                std::function<ConnectCallback> func{ [obj_ptr = this_ptr,func = std::forward<CallbackType>(callback)] (net::Peer&& who, [[maybe_unused]] std::uint32_t eventData) {
                    std::invoke(func,obj_ptr,std::forward<net::Peer>(who), eventData);
                } };
                if (netEvent == net::NetEvents::Connect) {
                    onConnect[hostIdx].push_back(std::move(func));
                }
                else {
                    onDisconnect[hostIdx].push_back(std::move(func));
                }
                return true;
            }
            if constexpr (std::is_same_v<CallbackType, MemberPacketCallback<This>>) {
                std::function<PacketCallback> func{ [obj_ptr = this_ptr,func = std::forward<CallbackType>(callback)] (net::Packet&& packet, [[maybe_unused]] std::uint32_t eventData) {
                    std::invoke(func,obj_ptr,std::forward<net::Packet>(packet), eventData);
                } };
                onReceive[hostIdx].push_back(std::move(func));
                return true;
            }
            return false;
        };
        void Poll(const net::Host& host, std::uint32_t timeout = 5000);
        void Poll(const net::Host_ptr& host, std::uint32_t timeout = 5000);
    private:
        std::size_t GetHostIdx(const net::Host&);
    private:
#if !defined(__clang__)
    #pragma warning(push)
    #pragma warning(disable : 4251)
#endif
        std::unordered_map<std::size_t, std::size_t> hosts{};
        std::vector<std::vector<std::function<ConnectCallback>>> onConnect{};
        std::vector<std::vector<std::function<ConnectCallback>>> onDisconnect{};
        std::vector<std::vector<std::function<PacketCallback>>> onReceive{};
#if !defined(__clang__)
    #pragma warning(push)
#endif
        std::hash<const Host*> hashFunc{};
    };
}