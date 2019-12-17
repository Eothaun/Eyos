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

	uint8_t Terrain::GetHeight(uint32_t x, uint32_t z) const {
		assert(IsCoordValid(x, z));

		return heightmap[z * GetMapWidth() + x];
	}

	//! NOTE: This function seems to work, but might be buggy. I have not tested it extensively
	bool Terrain::GetHeightAt(const glm::vec2& pos, glm::vec3* outHitPos, glm::vec3* outHitNormal) const {
		if (!IsCoordValid(pos)) {
			return false;
		}

		glm::uvec2 floorPos{ glm::floor(pos.x), glm::floor(pos.y) };
		glm::uvec2 ceilPos{ glm::ceil(pos.x), glm::ceil(pos.y) };
		
		uint8_t floorHeight = GetHeight(floorPos.x, floorPos.y);
		uint8_t heightUp = GetHeight(floorPos.x, ceilPos.y);
		uint8_t heightSide = GetHeight(ceilPos.x, floorPos.y);

		float floorWeight = 1 / glm::distance(pos, glm::vec2{ floorPos.x, floorPos.y });
		float heightUpWeight = 1 / glm::distance(pos, glm::vec2{ floorPos.x, ceilPos.y });
		float heightSideWeight = 1 / glm::distance(pos, glm::vec2{ ceilPos.x, floorPos.y });
		uint8_t height = (floorWeight * floorHeight + heightUpWeight * heightUp + heightSideWeight * heightSide) 
			/ (floorWeight + heightUpWeight + heightSideWeight);

		glm::vec3 flooredPos{ floorPos.x, floorHeight, floorPos.y };
		glm::vec3 heightUpPos{ floorPos.x, heightUp, ceilPos.y };
		glm::vec3 heightSidePos{ ceilPos.x, heightSide, floorPos.y };

		if (outHitPos) {
			*outHitPos = glm::vec3{ pos.x, height, pos.y };
		}
		if (outHitNormal) {
			glm::vec3 relativeHeightUp = glm::normalize( heightUpPos - flooredPos );
			glm::vec3 relativeHeightSide = glm::normalize( heightSidePos - flooredPos);

			*outHitNormal = glm::cross(relativeHeightUp, relativeHeightSide);
		}

		return true;
	}

	bool Terrain::Intersect(const eyos::Ray& pos, glm::vec3* outHitPos, glm::vec3* outHitNormal) const
	{
		assert(false && "Not implemented yet");
		return false;
	}
}