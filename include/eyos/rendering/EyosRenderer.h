#pragma once
#include <iostream>
#include <cstdint>
#include <memory>

#include "bgfx_utils.h"
#include <entry/entry.h>

#include "DebugRenderer.h"
#include "UIRenderer.h"
#include "eyos/ClientEcsType.h"


namespace eyos
{
	class Camera;

	class Renderer {
	public:
		Renderer();

		bool Init(uint32_t argc, char* argv[], uint32_t width, uint32_t height);
		void Render(EyosEcs& ecs, Camera& camera);
		bool Shutdown();

	private:
		void RenderModels(EyosEcs& ecs);
		void RenderInstancedModels(EyosEcs& ecs);

	public:
		uint32_t m_debug;
		uint32_t m_reset;

	private:
		std::unique_ptr<DebugRenderer> debugRenderer;
		std::unique_ptr<UIRenderer> uiRenderer;

		uint32_t m_width;
		uint32_t m_height;
		bgfx::VertexBufferHandle m_vbh;
		bgfx::IndexBufferHandle  m_ibh;
		bgfx::ProgramHandle m_program;

		bgfx::UniformHandle u_time;
		bgfx::ProgramHandle meshShaderProgram;

		int64_t m_timeOffset;
	};
}