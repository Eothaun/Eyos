// Note: Most code is from: http://www.chadvernon.com/blog/resources/directx9/terrain-generation-with-a-heightmap/

#include "eyos/rendering/RenderableTerrain.h"
#include "bgfx_utils.h"
#include "eyos/rendering/VertexLayouts.h"


namespace eyos
{
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    Summary: Generates vertices with a position, normal, and texture coordinates to create an indexed
    triangle strip plane.
    Parameters:
    [in/out] outVertices - Pointer to an array to be filled up.
    [in] verticesAlongWidth - Number of vertices along the width
    [in] verticesAlongLength - Number of vertices along the length
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    static void GeneratePositionTexturedWithHeight(std::vector<PosNormalUvVertex>& outVertices, int verticesAlongWidth, int verticesAlongLength, const std::vector<uint8_t>& pHeight)
    {
        outVertices.resize(verticesAlongLength * verticesAlongWidth);

        float halfWidth = ((float)verticesAlongWidth - 1.0f) / 2.0f;
        float halfLength = ((float)verticesAlongLength - 1.0f) / 2.0f;

        for (int z = 0; z < verticesAlongLength; z++)
        {
            for (int x = 0; x < verticesAlongWidth; x++)
            {
                glm::vec3 vertexPos{ (float)x - halfWidth,
                    (float)pHeight[z * verticesAlongLength + x],
                    (float)z - halfLength };
                glm::vec2 uv{ (float)x / (verticesAlongWidth - 1), (float)z / (verticesAlongLength - 1) };
                outVertices[z * verticesAlongLength + x] = PosNormalUvVertex(
                    vertexPos, glm::vec3{0, 1, 0}, uv
                );
            }
        }

        for (int z = 0; z < verticesAlongLength-1; z++)
        {
            for (int x = 0; x < verticesAlongWidth-1; x++)
            {
                glm::vec3 pos = outVertices[z * verticesAlongLength + x].pos;
                glm::vec3 deltaX = outVertices[(z)*verticesAlongLength + (x + 1)].pos - pos;
                glm::vec3 deltaZ = outVertices[(z + 1) * verticesAlongLength + (x)].pos - pos;;
                glm::vec3 normal = glm::cross(glm::normalize(deltaX), glm::normalize(deltaZ));
                outVertices[z * verticesAlongLength + x].normal = normal;
            }
        }
    }

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    Summary: Generates 32-bit indices for an indexed triangle strip plane.
    Parameters:
    [in/out] outIndices - Array to be filled up.
    [in] verticesAlongWidth - Number of vertices along the width
    [in] verticesAlongLength - Number of vertices along the length
    * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    static void GenerateIndices(std::vector<uint32_t>& outIndices, int verticesAlongWidth, int verticesAlongLength)
    {
        int numIndices = (verticesAlongWidth * 2) * (verticesAlongLength - 1) + (verticesAlongLength - 2);

        outIndices.resize(numIndices);

        int index = 0;
        for (int z = 0; z < verticesAlongLength - 1; z++)
        {
            // Even rows move left to right, odd rows move right to left.
            if (z % 2 == 0)
            {
                // Even row
                int x;
                for (x = 0; x < verticesAlongWidth; x++)
                {
                    outIndices[index++] = x + (z * verticesAlongWidth);
                    outIndices[index++] = x + (z * verticesAlongWidth) + verticesAlongWidth;
                }
                // Insert degenerate vertex if this isn't the last row
                if (z != verticesAlongLength - 2)
                {
                    outIndices[index++] = --x + (z * verticesAlongWidth);
                }
            }
            else
            {
                // Odd row
                int x;
                for (x = verticesAlongWidth - 1; x >= 0; x--)
                {
                    outIndices[index++] = x + (z * verticesAlongWidth);
                    outIndices[index++] = x + (z * verticesAlongWidth) + verticesAlongWidth;
                }
                // Insert degenerate vertex if this isn't the last row
                if (z != verticesAlongLength - 2)
                {
                    outIndices[index++] = ++x + (z * verticesAlongWidth);
                }
            }
        }
    }

	void RenderableTerrain::GenerateMesh()
	{
		std::unique_ptr<Mesh> mesh{ new Mesh() };
		Group vertexGroup{};

		std::vector<PosNormalUvVertex> vertices{};
        GeneratePositionTexturedWithHeight(vertices, terrain.GetWidth(), terrain.GetHeight(), terrain.GetHeightmap());

		const bgfx::Memory* vertexMemory = bgfx::copy(vertices.data(), vertices.size() * sizeof(PosNormalUvVertex));
		vertexGroup.m_vbh = bgfx::createVertexBuffer(vertexMemory, PosNormalUvVertex::ms_layout);
		assert(bgfx::isValid(vertexGroup.m_vbh));


		std::vector<uint32_t> indices{};
        GenerateIndices(indices, terrain.GetWidth(), terrain.GetHeight());
		
		const bgfx::Memory* indexMemory = bgfx::copy(indices.data(), indices.size() * sizeof(uint32_t));
		vertexGroup.m_ibh = bgfx::createIndexBuffer(indexMemory, BGFX_BUFFER_INDEX32);
		assert(bgfx::isValid(vertexGroup.m_ibh));

		mesh->m_groups.emplace_back(std::move(vertexGroup));
		mesh->m_layout = PosNormalUvVertex::ms_layout;

		generatedMesh = std::move(mesh);
	}
}