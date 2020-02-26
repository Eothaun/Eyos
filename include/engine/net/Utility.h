#include <cstring>
#include <cstdint>
#include <type_traits>

namespace eyos::net {
    // \biref bit casts: Casts a object from one trival copyable object to another trival type. If the size is the same.
    // \see https://en.cppreference.com/w/cpp/numeric/bit_cast
    // \see https://www.youtube.com/watch?v=_qzMpk-22cc
    template <class To, class From>
    [[nodiscard]] constexpr To
        bit_cast(const From& src) noexcept
    {
        static_assert(std::is_trivially_copyable_v<From>, "From Type needs to be trivially copyable");
        static_assert(std::is_trivial_v<To>, "To type needs to be trivial");
        static_assert((sizeof(To) == sizeof(From)), "Types need to be the same size");
        To dst;
        std::memcpy(&dst, &src, sizeof(To));
        return dst;
    }

	// \see https://github.com/MultiplayerBook/MultiplayerBook/blob/master/Chapter%204/RoboCat/Inc/ByteSwap.h
	[[nodiscard]] constexpr inline std::uint16_t ByteSwap2(std::uint16_t inData) noexcept
	{
		return (inData >> 8) | (inData << 8);
	}

	// \see https://github.com/MultiplayerBook/MultiplayerBook/blob/master/Chapter%204/RoboCat/Inc/ByteSwap.h
	[[nodiscard]] constexpr inline std::uint32_t ByteSwap4(std::uint32_t inData) noexcept
	{
		return  ((inData >> 24) & 0x000000ff) |
			((inData >> 8) & 0x0000ff00) |
			((inData << 8) & 0x00ff0000) |
			((inData << 24) & 0xff000000);
	}

	// \see https://github.com/MultiplayerBook/MultiplayerBook/blob/master/Chapter%204/RoboCat/Inc/ByteSwap.h
	[[nodiscard]] constexpr inline std::uint64_t ByteSwap8(std::uint64_t inData) noexcept
	{
		return  ((inData >> 56) & 0x00000000000000ff) |
			((inData >> 40) & 0x000000000000ff00) |
			((inData >> 24) & 0x0000000000ff0000) |
			((inData >> 8) & 0x00000000ff000000) |
			((inData << 8) & 0x000000ff00000000) |
			((inData << 24) & 0x0000ff0000000000) |
			((inData << 40) & 0x00ff000000000000) |
			((inData << 56) & 0xff00000000000000);
	}

	// \see https://github.com/MultiplayerBook/MultiplayerBook/blob/master/Chapter%204/RoboCat/Inc/ByteSwap.h
	template < typename tFrom, typename tTo >
	class TypeAliaser
	{
	public:
		TypeAliaser(tFrom inFromValue) :
			mAsFromType(inFromValue) {}
		tTo& Get() { return mAsToType; }

		union
		{
			tFrom 	mAsFromType;
			tTo		mAsToType;
		};
	};

	// \see https://github.com/MultiplayerBook/MultiplayerBook/blob/master/Chapter%204/RoboCat/Inc/ByteSwap.h
	//specialize for 1...
	template <typename T, size_t tSize > class ByteSwapper;
	template <typename T>
	class ByteSwapper< T, 1 >
	{
	public:
		T Swap(T inData) const
		{
			return inData;
		}
	};

	// \see https://github.com/MultiplayerBook/MultiplayerBook/blob/master/Chapter%204/RoboCat/Inc/ByteSwap.h
	//specialize for 2...
	template <typename T>
	class ByteSwapper< T, 2 >
	{
	public:
		T Swap(T inData) const
		{
			std::uint16_t result =
				ByteSwap2(TypeAliaser< T, std::uint16_t >(inData).Get());
			return TypeAliaser< std::uint16_t, T >(result).Get();
		}
	};

	// \see https://github.com/MultiplayerBook/MultiplayerBook/blob/master/Chapter%204/RoboCat/Inc/ByteSwap.h
	//specialize for 4...
	template <typename T>
	class ByteSwapper< T, 4 >
	{
	public:
		T Swap(T inData) const
		{
			std::uint32_t result =
				ByteSwap4(TypeAliaser< T, std::uint32_t >(inData).Get());
			return TypeAliaser< std::uint32_t, T >(result).Get();
		}
	};

	// \see https://github.com/MultiplayerBook/MultiplayerBook/blob/master/Chapter%204/RoboCat/Inc/ByteSwap.h
	//specialize for 8...
	template <typename T>
	class ByteSwapper< T, 8 >
	{
	public:
		T Swap(T inData) const
		{
			std::uint64_t result =
				ByteSwap8(TypeAliaser< T, std::uint64_t >(inData).Get());
			return TypeAliaser< std::uint64_t, T >(result).Get();
		}
	};

	template < typename T >
	T ByteSwap(T inData)
	{
		return ByteSwapper< T, sizeof(T) >().Swap(inData);
	}

}