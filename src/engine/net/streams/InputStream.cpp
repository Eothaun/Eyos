#include "engine/net/streams/InputStream.h"
#include "engine/net/Allocator.h"
#include "engine/net/Packet.h"
#include "engine/net/Common.h"
#include "engine/net/Utility.h"
#include "engine/Defines.h"

namespace {
	template<typename T>
	void add_data_to_buffer(std::byte* buffer,const T& value,std::size_t& head,std::size_t capacity) {
		assertm(head < capacity, "You cannot retrive, Stream is at its capacity");
		assertm((head + sizeof(T)) <= capacity, "You cannot retrive, Stream is at its capacity");
		std::memcpy(&buffer[head], &value, sizeof(T));
		head += sizeof(T);
	}
}

eyos::net::InputStream::~InputStream() {
	allocator.Free(buffer);
	buffer = nullptr;
}

eyos::net::InputStream::InputStream(Allocator& allocator):allocator { allocator }, capacity{ 1470 } {
	buffer = bit_cast<std::byte*>(allocator.Allocate(capacity));
}

eyos::net::InputStream::InputStream(Allocator& allocator, std::size_t bufferSize) : allocator{ allocator }, capacity{ bufferSize } {
	buffer = bit_cast<std::byte*>(allocator.Allocate(capacity));
}

eyos::net::InputStream::InputStream() : allocator{ GetNetworkAllocator() }, capacity{1470}{
}

eyos::net::InputStream::InputStream(std::size_t bufferSize) : allocator{ GetNetworkAllocator() }, capacity{ bufferSize } {
	buffer = bit_cast<std::byte*>(allocator.Allocate(capacity));
}

eyos::net::InputStream::InputStream(std::byte* otherBuffer, std::size_t size, Allocator& allocator) : capacity{ size }, allocator{ allocator }{
	buffer = bit_cast<std::byte*>(allocator.Allocate(size));
	memcpy(buffer, otherBuffer, size);
}

std::size_t eyos::net::InputStream::GetRemainingSize()
{
	return capacity - head;
}

eyos::net::Allocator& eyos::net::InputStream::GetAllocator() {
	return allocator;
}

eyos::net::InputStream& eyos::net::InputStream::operator<<(const bool& value) {
	add_data_to_buffer(buffer, value, head, capacity);
	return *this;
};
eyos::net::InputStream& eyos::net::InputStream::operator<<(const char& value) {
	add_data_to_buffer(buffer, value, head, capacity);
	return *this;
};
eyos::net::InputStream& eyos::net::InputStream::operator<<(const std::int8_t& value) {
	add_data_to_buffer(buffer, value, head, capacity);
	return *this;
};
eyos::net::InputStream& eyos::net::InputStream::operator<<(const std::uint8_t& value) {
	add_data_to_buffer(buffer, value, head, capacity);
	return *this;
};
eyos::net::InputStream& eyos::net::InputStream::operator<<(const std::int16_t& value) {
	add_data_to_buffer(buffer, htons(value), head, capacity);
	return *this;
};
eyos::net::InputStream& eyos::net::InputStream::operator<<(const std::uint16_t& value) {
	add_data_to_buffer(buffer, htons(value), head, capacity);
	return *this;
};
eyos::net::InputStream& eyos::net::InputStream::operator<<(const std::int32_t& value) {
	add_data_to_buffer(buffer, htonl(value), head, capacity);
	return *this;
};
eyos::net::InputStream& eyos::net::InputStream::operator<<(const std::uint32_t& value) {
	add_data_to_buffer(buffer, htonl(value), head, capacity);
	return *this;
};
eyos::net::InputStream& eyos::net::InputStream::operator<<(const std::int64_t& value) {
	add_data_to_buffer(buffer, ByteSwap(value), head, capacity);
	return *this;
};
eyos::net::InputStream& eyos::net::InputStream::operator<<(const std::uint64_t& value) {
	add_data_to_buffer(buffer, ByteSwap(value), head, capacity);
	return *this;
};

eyos::net::InputStream& eyos::net::InputStream::operator<<(const std::string& value) {
	*this << value.size();
	for (char chr : value){
		*this << chr;
	}
	return *this;
};
