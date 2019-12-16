#include "engine/Terrain.h"

#include <cassert>


namespace eyos
{
	Terrain::Terrain(char* heightmap, uint32_t width, uint32_t height)
		: width(width), height(height)
	{
		size_t mapSize = static_cast<size_t>(width)* static_cast<size_t>(height);
		this->heightmap.resize(mapSize);
		memcpy(&this->heightmap[0], heightmap, mapSize);
	}

	bool Terrain::Intersect(const glm::vec2& pos, glm::vec3* outHitPos, glm::vec3* outHitNormal) const
	{
		assert(false && "Not implemented yet");
		return false;
	}
}