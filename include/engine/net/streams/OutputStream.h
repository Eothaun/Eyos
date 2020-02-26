#pragma once
/*
Eyos Source Code License v1.0
Copyright (c) 2019-2020 Simon Renger
Last updated on February 16th, 2020.
*/
#include <cstddef>
#include <cstdint>
#include <string>
#include "engine/Defines.h"
namespace eyos::net {
    // forward declareations:
    class Packet;
    class InputStream;
    class Allocator;
    EYOS_API Allocator& GetNetworkAllocator();

    class EYOS_API OutputStream {
    public:
        OutputStream(Packet&& packet);
        OutputStream(Packet&& packet, Allocator& allocator);
        OutputStream(const OutputStream&) = delete;
        OutputStream(OutputStream&&) = default;
        OutputStream& operator=(const OutputStream&) = delete;
        OutputStream& operator=(OutputStream&&) = default;
        ~OutputStream();
    public:
        [[nodiscard]] std::size_t GetRemainingSize();
        OutputStream& operator>>( bool& value );
        OutputStream& operator>>( char& value );
        OutputStream& operator>>( std::string& value );
        OutputStream& operator>>( std::int8_t& value );
        OutputStream& operator>>( std::uint8_t& value );
        OutputStream& operator>>( std::int16_t& value );
        OutputStream& operator>>( std::uint16_t& value );
        OutputStream& operator>>( std::int32_t& value );
        OutputStream& operator>>( std::uint32_t& value );
        OutputStream& operator>>( std::int64_t& value );
        OutputStream& operator>>( std::uint64_t& value );
        [[nodiscard]] Allocator& GetAllocator();
    private:
        OutputStream(std::byte* buffer, std::size_t size,Allocator& allocator = GetNetworkAllocator());
        std::size_t head{};
        std::size_t capacity{};
        std::byte* buffer{};
        Allocator& allocator;
        template <typename PacketHeaderType>
        friend OutputStream StreamFromPacket(const PacketHeaderType packetType, Packet&& stream);
        friend EYOS_API OutputStream ToStream(InputStream&& stream);
        friend EYOS_API InputStream ToStream(OutputStream&& stream);
    };
}