#pragma once
#include <vector>
#include <cstddef>
#include <glm/glm.hpp>

#include "engine/Defines.hpp"
#include "geometry/Ray.h"


namespace eyos 
{
	// A heightmap based terrain
	class EYOS_API Terrain {
	public:
		Terrain() = default;
		Terrain(char* heightmap, uint32_t width, uint32_t height);

		bool GetHeightAt(const glm::vec2& pos, glm::vec3* outHitPos, glm::vec3* outHitNormal) const;
		bool Intersect(const eyos::Ray& pos, glm::vec3* outHitPos, glm::vec3* outHitNormal) const;

		bool IsCoordValid(uint32_t x, uint32_t z) const { return x < GetMapWidth() && z < GetMapDepth(); }
		bool IsCoordValid(glm::uvec2 coord) const { return coord.x < GetMapWidth() && coord.y < GetMapDepth(); }
		bool IsCoordValid(glm::vec2 coord) const { return coord.x >= 0.f && coord.y >= 0.f && coord.x < GetMapWidth() && coord.y < GetMapDepth(); }

		uint8_t GetHeight(uint32_t x, uint32_t z) const;
		//! Get the amount of elements in the X direction
		uint32_t GetMapWidth() const { return width; }
		//! Get the amount of elements in the Z direction
		uint32_t GetMapDepth() const { return height; }
		const std::vector<uint8_t>& GetHeightmap() const { return heightmap; }

	public:
		//! How big each pixel in the heightmap is in worldspace
		glm::vec2 tileSize{ 1, 1 };

	private:
		uint32_t width = 0;
		uint32_t height = 0;
		std::vector<uint8_t> heightmap;
	};
}
