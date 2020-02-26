#include <catch2/catch.hpp>
// eyos includes:
#include <engine/net/Common.h>
#include <engine/net/Packet.h>

#include <string>
using namespace eyos;

enum class TestEnum {
	Test
};

struct Trivial {
	int i{ 99 };
};

TEST_CASE("Create Empty packet", "[InputStream]") {
	net::Packet packet{ net::CreateEmptyPacket(TestEnum::Test) };
	REQUIRE(packet.Size() == sizeof(TestEnum));
}
TEST_CASE("Packet type == TestEnum Type", "[InputStream]") {
	net::Packet packet{ net::CreateEmptyPacket(TestEnum::Test) };
	auto type{ packet.Type<TestEnum>() };
	REQUIRE(type == TestEnum::Test);
}
TEST_CASE("Append data to packet", "[InputStream]") {
	net::Packet packet{ net::CreateEmptyPacket(TestEnum::Test) };
	Trivial trivialStruct{ 99 };
	Trivial trivialStructB{ 99 };
	const Trivial constTrivialStruct{ 99 };
	const Trivial constTrivialStructB{ 99 };
	REQUIRE(packet.Size() == sizeof(TestEnum));
	packet = std::move(net::AppendToPacket(std::move(packet), 42));
	REQUIRE(packet.Size() == sizeof(TestEnum)+sizeof(int));
	packet = std::move(net::AppendToPacket(std::move(packet), std::move(trivialStruct)));
	REQUIRE(packet.Size() == sizeof(TestEnum) + sizeof(int) + sizeof(trivialStruct));
	packet = std::move(net::AppendToPacket(std::move(packet), constTrivialStruct));
	REQUIRE(packet.Size() == sizeof(TestEnum) + sizeof(int) + sizeof(trivialStruct) + sizeof(constTrivialStruct));
	packet = std::move(net::AppendToPacket(std::move(packet), constTrivialStructB, sizeof(constTrivialStructB)));
	REQUIRE(packet.Size() == sizeof(TestEnum) + sizeof(int) + sizeof(trivialStruct) + sizeof(constTrivialStruct) + sizeof(constTrivialStructB));
	packet = std::move(net::AppendToPacket(std::move(packet), std::move(trivialStructB), sizeof(trivialStructB)));
	REQUIRE(packet.Size() == sizeof(TestEnum) + sizeof(int) + sizeof(trivialStruct) + sizeof(constTrivialStruct) + sizeof(constTrivialStructB) + sizeof(trivialStructB));
}