#include <catch2/catch.hpp>
// eyos includes:
#include <engine/net/Common.h>
#include <engine/net/streams/InputStream.h>
#include <engine/net/streams/OutputStream.h>

#include <string>
using namespace eyos;

enum class TestEnum {
	Test
};

template <typename = void>
constexpr std::size_t sum_helper()
{
	return 0u;
}

template <std::size_t I0, std::size_t ... Is>
constexpr std::size_t sum_helper()
{
	return I0 + sum_helper<Is...>();
}

template <typename ... Ts>
constexpr std::size_t sum_size(std::tuple<Ts...> const&)
{
	return sum_helper<sizeof(Ts)...>();
}

template <typename ... Ts>
constexpr std::size_t SizeOf() {
	return sum_size(std::tuple<Ts...>{});
}

TEST_CASE("Test test utility SizeOf", "[InputStream]") {
	REQUIRE(SizeOf<int,int,int>() == sizeof(int)*3);
}
TEST_CASE("Initiate A InputStream", "[InputStream]") {
	net::InputStream in{ 1024 };
	REQUIRE(in.GetRemainingSize() == 1024);
}
TEST_CASE("Add data to InputStream", "[InputStream]") {
	net::InputStream in{ 1024 };
	std::string testStr{ "Hallo World" };
	REQUIRE(in.GetRemainingSize() == 1024);
	in << true;
	REQUIRE(in.GetRemainingSize() == 1024- SizeOf<bool>());
	in << 42;
	REQUIRE(in.GetRemainingSize() == 1024- SizeOf<bool,int>());
	in << 'c';
	REQUIRE(in.GetRemainingSize() == 1024 - SizeOf<bool, int,char>());
	in << std::uint32_t{32};
	REQUIRE(in.GetRemainingSize() == 1024 - SizeOf<bool, int, char, std::uint32_t>());
	in << std::uint16_t{ 16 };
	REQUIRE(in.GetRemainingSize() == 1024 - SizeOf<bool, int, char,std::uint32_t, std::uint16_t>());
	in << std::uint64_t{ 64 };
	REQUIRE(in.GetRemainingSize() == 1024 - SizeOf<bool, int, char, std::uint32_t, std::uint16_t, std::uint64_t>());
	in << std::int32_t{ -32 };
	REQUIRE(in.GetRemainingSize() == 1024 - SizeOf<bool, int, char, std::uint32_t, std::uint16_t, std::uint64_t, std::int32_t>());
	in << std::int16_t{ -16 };
	REQUIRE(in.GetRemainingSize() == 1024 - SizeOf<bool, int, char, std::uint32_t, std::uint16_t, std::uint64_t, std::int32_t, std::int16_t>());
	in << std::int64_t{ -64 };
	REQUIRE(in.GetRemainingSize() == 1024 - SizeOf<bool, int, char, std::uint32_t, std::uint16_t, std::uint64_t, std::int32_t, std::int16_t, std::int64_t>());
	in << testStr;
	REQUIRE(in.GetRemainingSize() == 1024 - ((testStr.size() * sizeof(char)) + SizeOf<bool, int, char, std::uint32_t, std::uint16_t, std::uint64_t, std::int32_t, std::int16_t, std::int64_t, std::size_t>()));
}

TEST_CASE("Add large dataset to InputStream", "[InputStream]") {
	net::InputStream in{ 1024 };
	for (std::uint64_t value{ 0 }; value < 1024/sizeof(std::uint64_t); ++value) {
		in << value;
		auto size{ 1024 - ((value+1) * sizeof(std::uint64_t)) };
		REQUIRE(in.GetRemainingSize() == size);
	}
}

TEST_CASE("InputStream to Packet", "[InputStream]") {
	net::InputStream in{ 1024 };
	REQUIRE(in.GetRemainingSize() == 1024);
	auto packet{ StreamToPacket(TestEnum::Test,std::move(in)) };
	REQUIRE(packet.Size() == 1024+sizeof(TestEnum));
}

TEST_CASE("Packet to OutputStream", "[OutputStream]") {
	auto packet{ net::CreateEmptyPacket(TestEnum::Test) };
	net::OutputStream in{ std::move(packet) };
	REQUIRE(in.GetRemainingSize() == 0);
}
TEST_CASE("Stream Conversation", "[OutputStream]") {
	net::InputStream in{ 1024 };
	REQUIRE(in.GetRemainingSize() == 1024);
	REQUIRE(in.GetRemainingSize() == 1024);
	in << true;
	REQUIRE(in.GetRemainingSize() == 1024 - sizeof(bool));
	in << 42;
	REQUIRE(in.GetRemainingSize() == 1024 - (sizeof(bool) + sizeof(int)));
	in << false;
	REQUIRE(in.GetRemainingSize() == 1024 - (2*sizeof(bool) + sizeof(int)));
	SECTION("Convert InputStream to packet") {
		auto packet{ StreamToPacket(TestEnum::Test,std::move(in)) };
		REQUIRE(packet.Size() == 1024+sizeof(TestEnum));
		SECTION("Convert InputStream to packet") {
			net::OutputStream os{ std::move(packet) };
			REQUIRE(os.GetRemainingSize() == 1024);
		}
	}
	SECTION("Convert InputStream to Outputstream") {
		net::OutputStream out{ ToStream(std::move(in)) };
		REQUIRE(out.GetRemainingSize() == 1024);
		SECTION("Extract Data from Outputstream") {
			bool status{ false };
			int theAnswerToAllQuestions{ 0 };
			out >> status;
			REQUIRE(out.GetRemainingSize() == 1024-sizeof(bool));
			REQUIRE(status == true);
			out >> theAnswerToAllQuestions;
			REQUIRE(out.GetRemainingSize() == 1024 - (sizeof(bool)+sizeof(int)));
			REQUIRE(theAnswerToAllQuestions == 42);
			out >> status;
			REQUIRE(out.GetRemainingSize() == 1024 - (2*sizeof(bool) + sizeof(int)));
			REQUIRE(status == false);
		}
	}
}

TEST_CASE("Compare Added and Extracted large dataset to InputStream", "[InputStream]") {
	net::InputStream in{ 1024 };
	for (std::uint64_t value{ 0 }; value < 1024 / sizeof(std::uint64_t); ++value) {
		in << value;
		auto size{ 1024 - ((value + 1) * sizeof(std::uint64_t)) };
		REQUIRE(in.GetRemainingSize() == size);
	}
	net::OutputStream out{ ToStream(std::move(in)) };
	for (std::uint64_t value{ 0 }; value < 1024 / sizeof(std::uint64_t); ++value) {
		std::uint64_t i{ 0 };
		out >> i;
		auto size{ 1024 - ((value + 1) * sizeof(std::uint64_t)) };
		REQUIRE(out.GetRemainingSize() == size);
		REQUIRE(i == value);
	}
}

TEST_CASE("Add data to InputStream and Extract again", "[InputStream]") {
	net::InputStream in{ 1024 };
	std::string testStr{ "Hallo World" };
	in << true;
	in << 42;
	in << 'c';
	in << std::uint16_t{ 16 };
	in << std::uint32_t{ 32 };
	in << std::uint64_t{ 64 };
	in << std::int16_t{ -16 };
	in << std::int32_t{ -32 };
	in << std::int64_t{ -64 };
	in << testStr;
	net::OutputStream out{ ToStream(std::move(in)) };
	REQUIRE(out.GetRemainingSize() == 1024);
	bool status{ false };
	int intVal{ 0 };
	char charVal{ '\0' };
	std::uint16_t uint16Val{};
	std::uint32_t uint32Val{};
	std::uint64_t uint64Val{};
	std::int16_t int16Val{};
	std::int32_t int32Val{};
	std::int64_t int64Val{};
	std::string strVal{};
	out >> status;
	REQUIRE(out.GetRemainingSize() == 1024 - SizeOf<bool>());
	REQUIRE(status == true);
	out >> intVal;
	REQUIRE(out.GetRemainingSize() == 1024 - SizeOf<bool, int>());
	REQUIRE(intVal == 42);
	out >> charVal;
	REQUIRE(out.GetRemainingSize() == 1024 - SizeOf<bool, int, char>());
	REQUIRE(charVal == 'c');
	out >> uint16Val;
	REQUIRE(out.GetRemainingSize() == 1024 - SizeOf<bool, int, char, std::uint16_t>());
	REQUIRE(uint16Val == 16);
	out >> uint32Val;
	REQUIRE(out.GetRemainingSize() == 1024 - SizeOf<bool, int, char, std::uint16_t,std::uint32_t>());
	REQUIRE(uint32Val == 32);
	out >> uint64Val;
	REQUIRE(out.GetRemainingSize() == 1024 - SizeOf<bool, int, char, std::uint16_t, std::uint32_t,std::uint64_t>());
	REQUIRE(uint64Val == 64);
	out >> int16Val;
	REQUIRE(out.GetRemainingSize() == 1024 - SizeOf<bool, int, char, std::uint16_t, std::uint32_t, std::uint64_t,std::int16_t>());
	REQUIRE(int16Val == -16);
	out >> int32Val;
	REQUIRE(out.GetRemainingSize() == 1024 - SizeOf<bool, int, char, std::uint16_t, std::uint32_t, std::uint64_t, std::int16_t,std::int32_t>());
	REQUIRE(int32Val == -32);
	out >> int64Val;
	REQUIRE(out.GetRemainingSize() == 1024 - SizeOf<bool, int, char, std::uint16_t, std::uint32_t, std::uint64_t, std::int16_t, std::int32_t,std::int64_t>());
	REQUIRE(int64Val == -64);
	out >> strVal;
	REQUIRE(out.GetRemainingSize() == 1024 - ((testStr.size() * sizeof(char)) + SizeOf<bool, int, char, std::uint32_t, std::uint16_t, std::uint64_t, std::int32_t, std::int16_t, std::int64_t, std::size_t>()));
	REQUIRE(strVal == testStr);
}



