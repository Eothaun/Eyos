#pragma once
/*
MIT License

Copyright (c) 2019-2020 Simon Renger, Maiko Steeman, Marjolein Kaal, Hannes Vernooij

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "NetFwd.hpp"
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
        using PacketCallback = void(Packet && packet, [[maybe_unused]] std::uint32_t eventData);
        using PacketCallback_ = void(*)(Packet && packet, [[maybe_unused]] std::uint32_t eventData);
        using ConnectCallback = void(Peer && who, [[maybe_unused]] std::uint32_t eventData);
        using ConnectCallback_ = void(*)(Peer && who, [[maybe_unused]] std::uint32_t eventData);
        template <typename Member>
        using MemberPacketCallback = void (Member::*)(Packet && packet, [[maybe_unused]] std::uint32_t eventData);
        template <typename Member>
        using MemberConnectCallback = void (Member::*)(Peer && who, [[maybe_unused]] std::uint32_t eventData);
    public:
        template <typename CallbackType>
        bool AddCallback(const Host_ptr& host, NetEvents netEvent, std::function<CallbackType>&& callback)
        {
            auto hostIdx{ GetHostIdx(*host) };
            if constexpr (std::is_same_v<CallbackType, ConnectCallback>) {
                if (netEvent == NetEvents::Connect) {
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
        bool AddCallback(const Host_ptr& host, NetEvents netEvent, This* this_ptr, CallbackType&& callback)
        {
            return AddCallback(*host, netEvent, this_ptr, std::forward<CallbackType>(callback));
        }
        template <typename CallbackType>
        bool AddCallback(const Host_ptr& host, NetEvents netEvent, CallbackType&& callback)
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
        bool AddCallback(const Host& host, NetEvents netEvent, This* this_ptr, CallbackType&& callback)
        {
            auto hostIdx{ GetHostIdx(host) };
            if constexpr (std::is_same_v<CallbackType, MemberConnectCallback<This>>) {
                std::function<ConnectCallback> func{ [obj_ptr = this_ptr,func = std::forward<CallbackType>(callback)] (Peer&& who, [[maybe_unused]] std::uint32_t eventData) {
                    std::invoke(func,obj_ptr,std::forward<Peer>(who), eventData);
                } };
                if (netEvent == NetEvents::Connect) {
                    onConnect[hostIdx].push_back(std::move(func));
                }
                else {
                    onDisconnect[hostIdx].push_back(std::move(func));
                }
                return true;
            }
            if constexpr (std::is_same_v<CallbackType, MemberPacketCallback<This>>) {
                std::function<PacketCallback> func{ [obj_ptr = this_ptr,func = std::forward<CallbackType>(callback)] (Packet&& who, [[maybe_unused]] std::uint32_t eventData) {
                    std::invoke(func,obj_ptr,std::forward<Peer>(who), eventData);
                } };
                onReceive[hostIdx].push_back(std::move(func));
                return true;
            }
            return false;
        };
        void Poll(const Host& host, std::uint32_t timeout = 5000);
        void Poll(const Host_ptr& host, std::uint32_t timeout = 5000);
    private:
        std::size_t GetHostIdx(const Host&);
    private:
#pragma warning(push)
#pragma warning(disable : 4251)
        std::unordered_map<std::size_t, std::size_t> hosts{};
        std::vector<std::vector<std::function<ConnectCallback>>> onConnect{};
        std::vector<std::vector<std::function<ConnectCallback>>> onDisconnect{};
        std::vector<std::vector<std::function<PacketCallback>>> onReceive{};
#pragma warning(push)
        std::hash<const Host*> hashFunc{};
    };
}