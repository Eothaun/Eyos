#pragma once
#include <vector>
#include <cstddef>
#include <glm/glm.hpp>

#include "engine/Defines.hpp"


namespace eyos 
{
	// A heightmap based terrain
	class EYOS_API Terrain {
	public:
		Terrain() = default;
		Terrain(char* heightmap, uint32_t width, uint32_t height);

		bool Intersect(const glm::vec2& pos, glm::vec3* outHitPos, glm::vec3* outHitNormal) const;

		uint32_t GetWidth() const { return width; }
		uint32_t GetHeight() const { return height; }
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
