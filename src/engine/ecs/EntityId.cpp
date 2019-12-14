#include <ostream>

#include "engine/ecs/EntityId.h"


namespace eyos
{
	std::ostream& operator<<(std::ostream& os, const EntityId& id)
	{
		os << "EntityId{index: " << id.index << ", version: " << uint64_t{ id.version } << "}";
		return os;
	}
}
