#include <engine/net/Address.h>
#include <string>
namespace eyos::net {
///////////////////////////////
/// Address implementation ///
//////////////////////////////

Address::Address(ENetAddress* address)
    : enetAddress { *address } {};
Address::Address(const ENetAddress& address)
    : enetAddress { address } {};
Address::Address(const std::string& hostName, std::uint16_t port)
{
    ResolveHostName(hostName);
    enetAddress.port = port;
};
Address::Address(std::uint16_t port, std::uint32_t host)
    : enetAddress { host, port } {};

bool Address::ResolveHostIP(const std::string& ipaddress)
{
    auto status { enet_address_set_host_ip(&enetAddress, ipaddress.c_str()) };
    assertm(status == 0, "Could not resolve the ipaddress");
    return status == 0;
}
bool Address::ResolveHostName(const std::string& hostname)
{
    auto status { enet_address_set_host(&enetAddress, hostname.c_str()) };
    assertm(status == 0, "Could not resolve the ipaddress");
    return status == 0;
}

std::string Address::HostStr(std::size_t length)
{
    std::string host {};
    host.reserve(length);
    assertm(enet_address_get_host(&enetAddress, host.data(), length) == 0, "Cannot get Host");
    return host;
}
std::uint32_t Address::Host() { return enetAddress.host; }
std::string Address::Ip(std::size_t length)
{
    std::string ip {};
    ip.reserve(length);
    assertm(enet_address_get_host_ip(&enetAddress, ip.data(), ip.size()), "Cannot get ipaddress");
    return ip;
}
std::string Address::Ip6()
{
    return Ip(71);
}
std::string Address::Ip4()
{
    return Ip(35);
}
std::uint16_t Address::Port() { return enetAddress.port; }
}
