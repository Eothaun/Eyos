#pragma once
#include <vector>
#include <utility>

#include "bgfx_utils.h"

#include "VertexLayouts.h"


namespace Eyos 
{
	class DebugRenderer {
	public:
		const size_t VertexSize = sizeof(PosColorVertex);
		const size_t LineSize = VertexSize * 2;

	public:
		DebugRenderer();

		void AddLine(float posA[3], float posB[3], uint32_t color = 0xFF00FFFF);
		void AddLine(float posA[3], float posB[3], uint32_t colorA, uint32_t colorB);

		void ClearLines();

		void Render();

	public:
		bool useDepthTest = false;

	private:
		std::vector<std::pair<PosColorVertex, PosColorVertex>> lines;

		bgfx::ProgramHandle shaderProgram;
	};
}