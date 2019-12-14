﻿// EyosRenderer.cpp : Defines the entry point for the application.
//

#include "eyos/EyosRenderer.h"

#include <stdio.h>
#include <type_traits>

#include <bx/bx.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include "bgfx_utils.h"
#include <entry\entry.h>
#include <imgui\imgui.h>
#include <bx\timer.h>

#include "eyos/VertexLayouts.h"

namespace Eyos {
	static PosColorVertex s_cubeVertices[8] =
	{
		{-1.0f,  1.0f,  1.0f, 0xff000000 },
		{ 1.0f,  1.0f,  1.0f, 0xff0000ff },
		{-1.0f, -1.0f,  1.0f, 0xff00ff00 },
		{ 1.0f, -1.0f,  1.0f, 0xff00ffff },
		{-1.0f,  1.0f, -1.0f, 0xffff0000 },
		{ 1.0f,  1.0f, -1.0f, 0xffff00ff },
		{-1.0f, -1.0f, -1.0f, 0xffffff00 },
		{ 1.0f, -1.0f, -1.0f, 0xffffffff },
	};

	static const uint16_t s_cubeIndices[36] =
	{
		0, 1, 2, // 0
		1, 3, 2,
		4, 6, 5, // 2
		5, 6, 7,
		0, 2, 4, // 4
		4, 2, 6,
		1, 5, 3, // 6
		5, 7, 3,
		0, 4, 1, // 8
		4, 5, 1,
		2, 3, 6, // 10
		6, 3, 7,
	};

	Renderer::Renderer() = default;

	bool Renderer::Init(uint32_t argc, char* argv[], uint32_t width, uint32_t height)
	{
		Args args(argc, argv);

		m_width = width;
		m_height = height;
		m_debug = BGFX_DEBUG_TEXT;
		m_reset = BGFX_RESET_VSYNC;

		bgfx::Init init;
		init.type = args.m_type;
		init.vendorId = args.m_pciId;
		init.resolution.width = m_width;
		init.resolution.height = m_height;
		init.resolution.reset = m_reset;
		bgfx::init(init);

		// Enable debug text.
		bgfx::setDebug(m_debug);

		// Set view 0 clear state.
		bgfx::setViewClear(0
			, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
			, 0x303030ff
			, 1.0f
			, 0
		);

		InitVertexLayouts();

		// Create static vertex buffer.
		m_vbh = bgfx::createVertexBuffer(
			bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices))
			, PosColorVertex::ms_layout
		);

		// Create static index buffer.
		m_ibh = bgfx::createIndexBuffer(
			bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices))
		);

		// Create program from shaders.
		m_program = loadProgram("instancing/vs_instancing", "instancing/fs_instancing");
		meshShaderProgram = loadProgram("mesh/vs_mesh", "mesh/fs_mesh");

		bunnyMesh = meshLoad("meshes/Swordsman2.bin");

		u_time = bgfx::createUniform("u_time", bgfx::UniformType::Vec4);

		//bimg::ImageContainer* heightmap = imageLoad("maps/heightmap.png", bgfx::TextureFormat::RGBA8U);

		m_timeOffset = bx::getHPCounter();

		imguiCreate();

		debugRenderer = std::unique_ptr<DebugRenderer>{ new DebugRenderer() };
		uiRenderer = std::unique_ptr<UIRenderer>{ new UIRenderer(width, height) };

		//TODO: This leaks memory
		bgfx::TextureHandle barkTexture = loadTexture("textures/bark1.dds");
		float pos[2]{ 150, 150 };
		float size[2]{ 75, 75 };
		float depth = 20.f;
		uiRenderer->CreateImageWidget(pos, size, depth, barkTexture);

		return true;
	}

	void Renderer::Render()
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState))
		{
			imguiBeginFrame(m_mouseState.m_mx
				, m_mouseState.m_my
				, (m_mouseState.m_buttons[entry::MouseButton::Left] ? IMGUI_MBUT_LEFT : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Right] ? IMGUI_MBUT_RIGHT : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
				, m_mouseState.m_mz
				, uint16_t(m_width)
				, uint16_t(m_height)
			);

			ImGui::Begin("EyosRenderer ImGUI");
			ImGui::Text("%s", "EyosRenderer Imgui Test");
			ImGui::End();

			imguiEndFrame();

			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(0);

			float time = (float)((bx::getHPCounter() - m_timeOffset) / double(bx::getHPFrequency()));
			float zero = 0.0f;
			bgfx::setUniform(u_time, &time);
			//bgfx::setUniform(u_time, &time);

			// Get renderer capabilities info.
			const bgfx::Caps* caps = bgfx::getCaps();

			// Check if instancing is supported.
			if (0 == (BGFX_CAPS_INSTANCING & caps->supported))
			{
				assert(false, "Instancing is not supported on your GPU.");
			}
			
			const bx::Vec3 at = { 0.0f, 0.0f,   0.0f };
			const bx::Vec3 eye = { 0.0f, 0.0f, -35.0f };

			// Set view and projection matrix for view 0.
			{
				float view[16];
				bx::mtxLookAt(view, eye, at);

				float proj[16];
				bx::mtxProj(proj, 60.0f, float(m_width) / float(m_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
				bgfx::setViewTransform(0, view, proj);

				// Set view 0 default viewport.
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));
			}



			// 80 bytes stride = 64 bytes for 4x4 matrix + 16 bytes for RGBA color.
			const uint16_t instanceStride = 80;
			// 11x11 cubes
			const uint32_t numInstances = 121;

			if (numInstances == bgfx::getAvailInstanceDataBuffer(numInstances, instanceStride))
			{
				bgfx::InstanceDataBuffer idb;
				bgfx::allocInstanceDataBuffer(&idb, numInstances, instanceStride);

				uint8_t* data = idb.data;

				// Write instance data for 11x11 cubes.
				for (uint32_t yy = 0; yy < 11; ++yy)
				{
					for (uint32_t xx = 0; xx < 11; ++xx)
					{
						float* mtx = (float*)data;
						bx::mtxRotateXY(mtx, time + xx * 0.21f, time + yy * 0.37f);
						mtx[12] = -15.0f + float(xx) * 3.0f;
						mtx[13] = -15.0f + float(yy) * 3.0f;
						mtx[14] = 0.0f;

						float* color = (float*)&data[64];
						color[0] = bx::sin(time + float(xx) / 11.0f) * 0.5f + 0.5f;
						color[1] = bx::cos(time + float(yy) / 11.0f) * 0.5f + 0.5f;
						color[2] = bx::sin(time * 3.0f) * 0.5f + 0.5f;
						color[3] = 1.0f;

						data += instanceStride;
					}
				}

				// Set vertex and index buffer.
				bgfx::setVertexBuffer(0, m_vbh);
				bgfx::setIndexBuffer(m_ibh);

				// Set instance data buffer.
				bgfx::setInstanceDataBuffer(&idb);

				// Set render states.
				bgfx::setState(BGFX_STATE_DEFAULT);

				// Submit primitive for rendering to view 0.
				bgfx::submit(0, m_program);

			}
			
			for (GroupArray::const_iterator it = bunnyMesh->m_groups.begin(), itEnd = bunnyMesh->m_groups.end(); it != itEnd; ++it)
			{
				const Group& group = *it;

				bgfx::setIndexBuffer(group.m_ibh);
				bgfx::setVertexBuffer(0, group.m_vbh);

				float translationMatrix[16];
				bx::mtxTranslate(translationMatrix, 0, -5, -25);
				float timedRotation[16];
				bx::mtxRotateXY(timedRotation, 3.14 / 2, time / 2.5f);
				float scaleMatrix[16];
				bx::mtxScale(scaleMatrix, 0.25);
				float modelMatrix[16];
				bx::mtxIdentity(modelMatrix);
				bx::mtxMul(modelMatrix, modelMatrix, scaleMatrix);
				bx::mtxMul(modelMatrix, modelMatrix, timedRotation);
				bx::mtxMul(modelMatrix, modelMatrix, translationMatrix);

				bgfx::setTransform(modelMatrix);
				bgfx::setState((0
					| BGFX_STATE_WRITE_RGB
					| BGFX_STATE_WRITE_A
					| BGFX_STATE_WRITE_Z
					| BGFX_STATE_DEPTH_TEST_LESS
					| BGFX_STATE_CULL_CCW
					| BGFX_STATE_MSAA
					));

				bgfx::submit(0, meshShaderProgram, 0, it != itEnd - 1);
			}

			uiRenderer->Render();

			//TODO: Remove this, it's just for testing
			{
				float pA[3]{ 0, 0, -15 };
				float pB[3]{ sin(time) * 5, cos(time) * 5, -15 };
				debugRenderer->AddLine(pA, pB);
			}
			{
				float pA[3]{ -6, 0, -15 };
				float pB[3]{ sin(time) * 5 - 6, cos(time) * 5, -15 };
				debugRenderer->AddLine(pA, pB, 0xFF0000FF);
			}
			{
				float pA[3]{ 0, 6, -15 };
				float pB[3]{ sin(time) * 5, cos(time) * 5 + 6, -15 };
				debugRenderer->AddLine(pA, pB, 0xFF0000FF);
			}
			{
				float pA[3]{ 0, -6, -15 };
				float pB[3]{ sin(time) * 5, cos(time) * 5 - 6, -15 };
				debugRenderer->AddLine(pA, pB, 0xFF0000FF);
			}

			//Do the debug drawing
			debugRenderer->Render();
			debugRenderer->ClearLines();

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			bgfx::frame();
		}
	}

	bool Renderer::Shutdown()
	{
		//Destroy the pointer
		uiRenderer.reset();
		debugRenderer.reset();

		imguiDestroy();

		// Cleanup.
		bgfx::destroy(m_ibh);
		bgfx::destroy(m_vbh);
		bgfx::destroy(m_program);

		// Shutdown bgfx.
		bgfx::shutdown();

		return true;
	}
}