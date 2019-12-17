#pragma once
#include <vector>
#include <utility>

#include "bgfx_utils.h"
#include <glm/glm.hpp>

#include "VertexLayouts.h"


namespace eyos
{
	class DebugRenderer {
	public:
		const size_t VertexSize = sizeof(PosColorVertex);
		const size_t LineSize = VertexSize * 2;

	public:
		DebugRenderer();

		void AddLine(glm::vec3 posA, glm::vec3 posB, float time = 0.f, uint32_t color = 0xFF00FFFF);
		void AddLine(glm::vec3 posA, glm::vec3 posB, float time, uint32_t colorA, uint32_t colorB);

		void ClearLines();

		void Render();

	private:
		void CheckLineLifetimes();

	public:
		bool useDepthTest = true;

	private:
		std::vector<std::pair<PosColorVertex, PosColorVertex>> lines;
		std::vector<float> linesAliveUntil;

		bgfx::ProgramHandle shaderProgram;
		uint64_t startTime;
	};
}