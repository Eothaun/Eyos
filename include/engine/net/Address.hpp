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
