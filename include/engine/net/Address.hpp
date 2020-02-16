#pragma once
/*
Eyos Source Code License v1.0
Copyright (c) 2019-2020 Simon Renger, Maiko Steeman, Marjolein Kaal, Hannes Vernooij
Last updated on February 16th, 2020.
*/
#include "NetFwd.hpp"
#include <string>
namespace eyos::net {
/*
    ports 49152 to 65535 are known as dynamic ports. These are never assigned by IANA
    and are fair game for any process to use. If a process attempts to bind to a dynamic port and
    finds that it is in use, it should handle that gracefully by attempting to bind to other dynamic
    ports until an available one is found. As a good Internet citizen, you should use only dynamic
    ports while building your multiplayer games, and then register with IANA for a user port
    assignment if necessary. - Page 40
 */
class EYOS_API Address {
public:
    Address(ENetAddress*);
    Address(const ENetAddress&);
    Address(std::uint16_t port = 49200, std::uint32_t host = ENET_HOST_ANY);
    Address(const std::string& hostName, std::uint16_t port);
    Address(const Address&) = default;
    Address(Address&&) = default;
    Address& operator=(const Address&) = default;
    Address& operator=(Address&&) = default;

public:
    bool ResolveHostName(const std::string& hostname);
    bool ResolveHostIP(const std::string& ipaddress);

    [[nodiscard]] std::string HostStr(std::size_t hostLength = 64);
    [[nodiscard]] std::uint32_t Host();
    [[nodiscard]] std::string Ip4();
    [[nodiscard]] std::string Ip6();
    [[nodiscard]] std::string Ip(std::size_t length);
    [[nodiscard]] std::uint16_t Port();

private:
    ENetAddress enetAddress { ENET_HOST_ANY, 49200 };
    //friends:
    friend EYOS_API class Host;
};
}
