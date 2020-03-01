#pragma once
#include <cstdint>
#include <ostream>
#include "engine/Defines.h"

namespace eyos {
	struct EYOS_API EntityId
	{
	public:
		using Index_t = uint32_t;
		using Version_t = uint8_t;

		static_assert(std::is_unsigned_v<Version_t>,
			"We rely on overflowing for the version. To make sure there is no undefined behaviour, it's required to use an unsigned integer type");

		EntityId() : index(0), version(0) {}
		explicit EntityId(Index_t index, Version_t version = 0) : index(index), version(version) {}

		friend bool operator==(const EntityId& lhs, const EntityId& rhs)
		{
			return lhs.index == rhs.index
				&& lhs.version == rhs.version;
		}
		friend bool operator!=(const EntityId& lhs, const EntityId& rhs) { return !(lhs == rhs); }
		friend bool operator<(const EntityId& lhs, const EntityId& rhs)
		{
			// version is not compared. because the entity Id represents an index in an array
			// And the version is designed to wrap around constantly.
			return lhs.index < rhs.index;
		}
		friend bool operator<=(const EntityId& lhs, const EntityId& rhs) { return !(rhs < lhs); }
		friend bool operator>(const EntityId& lhs, const EntityId& rhs) { return rhs < lhs; }
		friend bool operator>=(const EntityId& lhs, const EntityId& rhs) { return !(lhs < rhs); }

	public:
		static constexpr Index_t InvalidIndex = /*pow(2,24)-1 =*/ 16'777'215;

		Index_t index : 24;
		Version_t version;
	};

	EYOS_API std::ostream& operator<<(std::ostream& os, const EntityId& id);
}

namespace std
{
	template<>
	struct hash<eyos::EntityId>
	{
		std::size_t operator()(const eyos::EntityId& id) const noexcept
		{
			uint64_t total_val = id.version;
			total_val <<= sizeof(uint64_t) - sizeof(eyos::EntityId::Version_t);
			total_val ^= id.index;

			return std::hash<uint64_t>{}(total_val);
		}
	};
}
