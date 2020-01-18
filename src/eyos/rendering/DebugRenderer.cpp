#include "eyos/rendering/DebugRenderer.h"
#include <bx/timer.h>

#include <array>
#include <numeric>



namespace eyos
{
	DebugRenderer::DebugRenderer() {
		shaderProgram = loadProgram("cubes/vs_cubes", "cubes/fs_cubes");

		startTime = bx::getHPCounter();
	}

	void DebugRenderer::AddLine(glm::vec3 posA, glm::vec3 posB, float time, uint32_t color)
	{
		float currentTime = (float)((bx::getHPCounter() - startTime) / double(bx::getHPFrequency()));

		lines.emplace_back(PosColorVertex{ posA[0], posA[1], posA[2], color }, PosColorVertex{ posB[0], posB[1], posB[2], color });
		linesAliveUntil.push_back(currentTime + time);
	}
	void DebugRenderer::AddLine(glm::vec3 posA, glm::vec3 posB, float time, uint32_t colorA, uint32_t colorB)
	{
		float currentTime = (float)((bx::getHPCounter() - startTime) / double(bx::getHPFrequency()));

		lines.emplace_back(PosColorVertex{ posA[0], posA[1], posA[2], colorA }, PosColorVertex{ posB[0], posB[1], posB[2], colorB });
		linesAliveUntil.push_back(currentTime + time);
	}

	void DebugRenderer::ClearLines()
	{
		lines.clear();
		linesAliveUntil.clear();
	}

	void DebugRenderer::Render()
	{
		uint64_t state = 0
			| BGFX_STATE_WRITE_R
			| BGFX_STATE_WRITE_G
			| BGFX_STATE_WRITE_B
			| BGFX_STATE_WRITE_A
//			| BGFX_STATE_WRITE_Z
			| (useDepthTest ? BGFX_STATE_DEPTH_TEST_LESS : 0)
			| BGFX_STATE_CULL_CW
			| BGFX_STATE_MSAA
			| BGFX_STATE_PT_LINES
			;

		std::array<float, 16> identityMatrix{};
		identityMatrix[4 * 0 + 0] = 1.0f;
		identityMatrix[4 * 1 + 1] = 1.0f;
		identityMatrix[4 * 2 + 2] = 1.0f;
		identityMatrix[4 * 3 + 3] = 1.0f;

		bgfx::setTransform(identityMatrix.data());

		const bgfx::Memory* lineMemory = bgfx::copy(lines.data(), lines.size() * LineSize);
		bgfx::DynamicVertexBufferHandle vtxHandle = bgfx::createDynamicVertexBuffer(lineMemory, PosColorVertex::ms_layout);
		bgfx::setVertexBuffer(0, vtxHandle);
		bgfx::destroy(vtxHandle);

		/*const bgfx::Memory* idxMemory = bgfx::alloc(sizeof(uint32_t) * lines.size() * 2);
		std::iota(reinterpret_cast<uint32_t*>(idxMemory->data), reinterpret_cast<uint32_t*>(idxMemory->data) + lines.size() * 2, 0);
		bgfx::DynamicIndexBufferHandle idxHandle = bgfx::createDynamicIndexBuffer(idxMemory, BGFX_BUFFER_INDEX32);
		bgfx::setIndexBuffer(idxHandle);
		bgfx::destroy(idxHandle);*/

		bgfx::setState(state);
		
		bgfx::submit(0, shaderProgram);

		CheckLineLifetimes();
	}

	void DebugRenderer::CheckLineLifetimes()
	{
		float currentTime = (float)((bx::getHPCounter() - startTime) / double(bx::getHPFrequency()));
		
		auto aliveIt = linesAliveUntil.begin();
		auto linesIt = lines.begin();
		while (aliveIt != linesAliveUntil.end()) {
			if (*aliveIt <= currentTime) {
				aliveIt = linesAliveUntil.erase(aliveIt);
				linesIt = lines.erase(linesIt);
			} else {
				++aliveIt;
				++linesIt;
			}
		}
	}
}