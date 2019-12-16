#pragma once
#include <memory>
#include <vector>

#include "engine/Terrain.h"
#include "eyos/rendering/Material.h"



struct Mesh;

namespace eyos 
{
	// Terrain with added data for it to be rendered, like textures, and mesh.
	class RenderableTerrain
	{
	public:
		RenderableTerrain() = default;
		RenderableTerrain(char* heightmap, uint32_t width, uint32_t height) : terrain(heightmap, width, height) {}

		void GenerateMesh();

	public:
		Terrain terrain;
		std::unique_ptr<Mesh> generatedMesh;
		std::vector<std::unique_ptr<Material>> materials;

	};
}