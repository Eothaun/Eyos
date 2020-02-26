#include "engine/net/streams/OutputStream.h"
#include "engine/net/Allocator.h"
#include "engine/net/Packet.h"
#include "engine/net/Common.h"
#include "engine/net/Utility.h"
#include "engine/Defines.h"

#include <cstddef>
#include <functional>

namespace {
	template<typename T>
	void get_data_from_buffer(std::byte * buffer,T & value, std::size_t & head, std::size_t capacity) {
			assertm(head < capacity, "You cannot retrive, Stream is at its capacity");
			assertm((head + sizeof(T)) <= capacity, "You cannot retrive, Stream is at its capacity");
			value = *eyos::net::bit_cast<T*>(&buffer[head]);
			head += sizeof(T);
	}
	template<typename T>
	void get_data_from_buffer(std::byte* buffer, T& value, std::size_t& head, std::size_t capacity, std::function<T(T)> function) {
		get_data_from_buffer(buffer, value, head, capacity);
		value = function(value);
	}
}

eyos::net::OutputStream::OutputStream(std::byte* otherBuffer, std::size_t size,Allocator& allocator) :allocator{ allocator },capacity{ size }{
	buffer = bit_cast<std::byte*>(allocator.Allocate(size));
	memcpy(buffer, otherBuffer, size);
}



eyos::net::OutputStream::OutputStream(Packet&& packet) : allocator{ GetNetworkAllocator() }, capacity{ packet.Size() - packet.typeSize }, buffer{ bit_cast<std::byte*>(allocator.Allocate(packet.Size() - packet.typeSize))}
{
	memcpy(buffer, packet.Data(packet.typeSize), capacity);
	packet.Destroy();
}

eyos::net::OutputStream::OutputStream(Packet&& packet, Allocator& allocator) : allocator{ allocator }, capacity{ packet.Size() - packet.typeSize }, buffer{ bit_cast<std::byte*>(allocator.Allocate(packet.Size() - packet.typeSize)) }
{
	memcpy(buffer, packet.Data(packet.typeSize), capacity);
	packet.Destroy();
}

eyos::net::OutputStream::~OutputStream()
{
	allocator.Free(buffer);
	buffer = nullptr;
}

[[nodiscard]] std::size_t eyos::net::OutputStream::GetRemainingSize() {
	return capacity-head;
};
[[nodiscard]] eyos::net::Allocator& eyos::net::OutputStream::GetAllocator() { return allocator; };
eyos::net::OutputStream& eyos::net::OutputStream::operator>>(bool& value) {
	get_data_from_buffer(buffer, value, head, capacity);
	return *this;
};
eyos::net::OutputStream& eyos::net::OutputStream::operator>>(char& value) {
	get_data_from_buffer(buffer, value, head, capacity);
	return *this;
};
eyos::net::OutputStream& eyos::net::OutputStream::operator>>(std::int8_t& value) {
	get_data_from_buffer(buffer, value, head, capacity);
	return *this;
};
eyos::net::OutputStream& eyos::net::OutputStream::operator>>(std::uint8_t& value) {
	get_data_from_buffer(buffer, value, head, capacity);
	return *this;
};
eyos::net::OutputStream& eyos::net::OutputStream::operator>>(std::int16_t& value) {
	get_data_from_buffer<std::int16_t>(buffer, value, head, capacity, ntohs);
	return *this;
};
eyos::net::OutputStream& eyos::net::OutputStream::operator>>(std::uint16_t& value) {
	get_data_from_buffer<std::uint16_t>(buffer, value, head, capacity, ntohs);
	return *this;
};
eyos::net::OutputStream& eyos::net::OutputStream::operator>>(std::int32_t& value) {
	get_data_from_buffer<std::int32_t>(buffer, value, head, capacity, ntohl);
	return *this;
};
eyos::net::OutputStream& eyos::net::OutputStream::operator>>(std::uint32_t& value) {
	get_data_from_buffer<std::uint32_t>(buffer, value, head, capacity, ntohl);
	return *this;
};
eyos::net::OutputStream& eyos::net::OutputStream::operator>>(std::int64_t& value) {
	get_data_from_buffer<std::int64_t>(buffer, value, head, capacity, ByteSwap8);
	return *this;
};
eyos::net::OutputStream& eyos::net::OutputStream::operator>>(std::uint64_t& value) {
	get_data_from_buffer<std::uint64_t>(buffer, value, head, capacity, ByteSwap8);
	return *this;
};
eyos::net::OutputStream& eyos::net::OutputStream::operator>>(std::string& value) {
	std::size_t length{};
	*this >> length;
	value.resize(length);
	for (auto& chr : value) {
		*this >> chr;
	}
	return *this;
};
