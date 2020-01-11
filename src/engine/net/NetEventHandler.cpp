#include <engine/net/NetEventHandler.hpp>
#include <engine/net/Host.hpp>
#include <engine/net/Peer.hpp>
#include <engine/net/Packet.hpp>
namespace eyos::net {
    //////////////////////////////////////
    /// NetEventHandler implementation ///
    /////////////////////////////////////
    std::size_t NetEventHandler::GetHostIdx(const Host& host)
    {
        auto hashVal{ hashFunc(&host) };
        auto itr{ std::find_if(hosts.begin(), hosts.end(), [hashVal](auto const& hash) {
            return hash.first == hashVal;
        }) };
        if (itr == std::end(hosts)) {
            onConnect.push_back({});
            onDisconnect.push_back({});
            onReceive.push_back({});
            hosts.insert({ hashVal, onConnect.size() - 1 });
            return onConnect.size() - 1;
        }
        return itr->second;
    }
    void NetEventHandler::Poll(const Host_ptr& host, std::uint32_t timeout)
    {
        Poll(*host, timeout);
    }
    void NetEventHandler::Poll(const Host& host, std::uint32_t timeout)
    {
        auto hostIdx{ GetHostIdx(host) };
        auto invoke = [](const auto& callbableContainer, auto idx, auto&&... params) {
            for (const auto& callable : callbableContainer[idx]) {
                callable(std::forward<decltype(params)>(params)...);
            }
        };
        net::Event event{};
        while (enet_host_service(host.enetHost, &event, 5000) > 0) {
            auto eventType{ static_cast<NetEvents>(event.type) };
            switch (eventType) {
            case NetEvents::Connect: {
                invoke(onConnect, hostIdx, Peer{ event.peer }, static_cast<std::uint32_t>(event.data));
            } break;
            case NetEvents::Disconnect:
                invoke(onDisconnect, hostIdx, Peer{ event.peer }, static_cast<std::uint32_t>(event.data));
                break;
            case NetEvents::Receive:
                invoke(onReceive, hostIdx, Packet{ event.packet }, static_cast<std::uint32_t>(event.data));
                break;
            default:
                break;
            }
        }
    }
}