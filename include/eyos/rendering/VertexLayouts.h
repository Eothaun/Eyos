#pragma once
#include "bgfx_utils.h"
#include <glm/glm.hpp>


namespace eyos {
	struct PosColorVertex
	{
		float m_x;
		float m_y;
		float m_z;
		uint32_t m_abgr;

		static void init()
		{
			ms_layout
				.begin()
				.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
				.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
				.end();
		};

		static bgfx::VertexLayout ms_layout;
	};

	struct PosColorUvVertex
	{
		float m_x;
		float m_y;
		float m_z;
		uint32_t m_abgr;
		float u;
		float v;

		static void init()
		{
			ms_layout
				.begin()
				.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
				.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
				.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
				.end();
		}

		static bgfx::VertexLayout ms_layout;
	};

	struct PosNormalUvVertex
	{
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 uv;

		PosNormalUvVertex() = default;
		PosNormalUvVertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 uv)
			: pos(pos), normal(normal), uv(uv) {}

		static void init()
		{
			ms_layout
				.begin()
				.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
				.add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float)
				.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
				.end();
		}

		static bgfx::VertexLayout ms_layout;
	};



	inline void InitVertexLayouts() {
		static bool layoutsInitialized = false;
		if (!layoutsInitialized) {
			PosColorVertex::init();
			PosColorUvVertex::init();
			PosNormalUvVertex::init();

			layoutsInitialized = true;
		}
	}
}
