#include "eyos/rendering/UIRenderer.h"
#include <cassert>
#include <numeric>
#include <array>

#include "eyos/rendering/VertexLayouts.h"
#include "entry/entry.h"
#include <bx\timer.h>


namespace eyos {
	UI::Widget::~Widget() = default;

	static TrueTypeHandle loadTtf(FontManager* _fm, const char* _filePath)
	{
		uint32_t size;
		void* data = load(_filePath, &size);

		if (NULL != data)
		{
			TrueTypeHandle handle = _fm->createTtf((uint8_t*)data, size);
			BX_FREE(entry::getAllocator(), data);
			return handle;
		}

		TrueTypeHandle invalid = BGFX_INVALID_HANDLE;
		return invalid;
	}

	UIRenderer::UIRenderer(uint32_t width, uint32_t height) : screenWidth(width), screenHeight(height)
	{
		shaderProgram = loadProgram("unlit_textured/vs_unlit_textured_color", "unlit_textured/fs_unlit_textured_color");

		textureUniform = bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);

		// Init the text rendering system.
		fontManager = std::unique_ptr<FontManager>{ new FontManager(512) };
		textBufferManager = std::unique_ptr<TextBufferManager>{ new TextBufferManager(fontManager.get()) };

		ttfHandle = loadTtf(fontManager.get(), "fonts/roboto-bold.ttf");
		fontHandle = fontManager->createFontByPixelSize(ttfHandle, 0, 32);

		transientTextBuffer = textBufferManager->createTextBuffer(FONT_TYPE_ALPHA, BufferType::Transient);
	}

	UIRenderer::~UIRenderer()
	{
		fontManager->destroyTtf(ttfHandle);
		fontManager->destroyFont(fontHandle);

		textBufferManager->destroyTextBuffer(transientTextBuffer);


		bgfx::destroy(vtxBufferHandle);
		bgfx::destroy(idxBufferHandle);

		bgfx::destroy(textureUniform);
		bgfx::destroy(shaderProgram);
	}

	UI::ImageWidget* UIRenderer::CreateImageWidget(float pos[2], float size[2], float depth, bgfx::TextureHandle texture)
	{
		UI::ImageWidget* widget = imageWidgets.emplace_back(new UI::ImageWidget{ pos, size, depth, texture }).get();

		return widget;
	}
	UI::TextWidget* UIRenderer::CreateTextWidget(float pos[2], float size[2], float depth, std::string_view text)
	{
		assert(false && "Not implemented yet!");

		//TODO: Generate text texture;
		bgfx::TextureHandle textTexture = { 0 };

		UI::TextWidget* widget = textWidgets.emplace_back(new UI::TextWidget{ pos, size, depth, std::string{text}, textTexture }).get();

		return widget;
	}
	void UIRenderer::DestoyImageWidget(UI::ImageWidget* imageWidget)
	{
		auto imageWidgetIt = std::find_if(imageWidgets.begin(), 
			imageWidgets.end(), [imageWidget](const std::unique_ptr<UI::ImageWidget>& unique_ptr) { return unique_ptr.get() == imageWidget; });

		if (imageWidgetIt != imageWidgets.end()) {
			std::swap(*imageWidgetIt, imageWidgets.back());
			imageWidgets.erase(--imageWidgets.end());
		}
	}
	void UIRenderer::DestoyTextWidget(UI::TextWidget* textWidget)
	{
		auto textWidgetIt = std::find_if(textWidgets.begin(),
			textWidgets.end(), [textWidget](const std::unique_ptr<UI::TextWidget>& unique_ptr) { return unique_ptr.get() == textWidget; });

		if (textWidgetIt != textWidgets.end()) {
			std::swap(*textWidgetIt, textWidgets.back());
			textWidgets.erase(--textWidgets.end());
		}
	}
	void UIRenderer::ClearAll()
	{
		imageWidgets.clear();
		textWidgets.clear();
	}
	void UIRenderer::Render()
	{
		/// Not efficient yet, but it works!

		uint64_t state = 0
			| BGFX_STATE_WRITE_R
			| BGFX_STATE_WRITE_G
			| BGFX_STATE_WRITE_B
			| BGFX_STATE_WRITE_A
			| BGFX_STATE_WRITE_Z
			| BGFX_STATE_DEPTH_TEST_LESS
//			| BGFX_STATE_CULL_CW
			| BGFX_STATE_MSAA
//			| BGFX_STATE_PT_LINES
			;

		float identityMatrix[16];
		bx::mtxIdentity(identityMatrix);

		float viewMatrix[16];
		bx::mtxIdentity(viewMatrix);
		//bx::mtxLookAt(viewMatrix, { 0, 0, 35 }, { 0, 0, -35 });

		float projectionMatrix[16];
		bx::mtxOrtho(projectionMatrix, 0, screenWidth, screenHeight, 0, -100, 100, 0, bgfx::getCaps()->homogeneousDepth);
		
		bgfx::setViewTransform(1, viewMatrix, projectionMatrix);
		bgfx::setViewRect(1, 0, 0, uint16_t(screenWidth), uint16_t(screenHeight));
		bgfx::setViewClear(1, BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL);

		bgfx::setTransform(identityMatrix);

		int64_t now = bx::getHPCounter();
		static int64_t last = now;
		const int64_t frameTime = now - last;
		last = now;
		const double freq = double(bx::getHPFrequency());
		const double toMs = 1000.0 / freq;

		// Use transient text to display debug information.
		char fpsText[64];
		bx::snprintf(fpsText, BX_COUNTOF(fpsText), "Frame: % 7.3f[ms]", double(frameTime) * toMs);

		textBufferManager->clearTextBuffer(transientTextBuffer);
		textBufferManager->setPenPosition(transientTextBuffer, screenWidth - 210.0f, 10.0f);
		textBufferManager->appendText(transientTextBuffer, fontHandle, "Transient\n");
		textBufferManager->appendText(transientTextBuffer, fontHandle, "text buffer\n");
		textBufferManager->appendText(transientTextBuffer, fontHandle, fpsText);
		// Submit the debug text.
		textBufferManager->submitTextBuffer(transientTextBuffer, 1);

		for (auto& imageWidget : imageWidgets) {
			const bgfx::Memory* vertexMemory = bgfx::alloc(sizeof(PosColorUvVertex) * 4);
			const bgfx::Memory* indexMemory = bgfx::alloc(sizeof(uint32_t) * 6);
			GenerateQuad(imageWidget->pos, imageWidget->size, imageWidget->depth, reinterpret_cast<PosColorUvVertex*>(vertexMemory->data), reinterpret_cast<uint32_t*>(indexMemory->data));
			
			vtxBufferHandle = bgfx::createDynamicVertexBuffer(vertexMemory, PosColorUvVertex::ms_layout);
			bgfx::setVertexBuffer(0, vtxBufferHandle);
			bgfx::destroy(vtxBufferHandle);

			idxBufferHandle = bgfx::createDynamicIndexBuffer(indexMemory, BGFX_BUFFER_INDEX32);
			bgfx::setIndexBuffer(idxBufferHandle);
			bgfx::destroy(idxBufferHandle);

			bgfx::setTexture(0, textureUniform, imageWidget->texture);
			
			bgfx::setState(state);

			bgfx::submit(1, shaderProgram);
		}
	}

	void UIRenderer::OnResolutionChanged(uint32_t newWidth, uint32_t newHeight)
	{
		screenWidth = newWidth;
		screenHeight = newHeight;
	}

	void UIRenderer::GenerateQuad(float pos[2], float size[2], float depth, void* outVertices, uint32_t outIndices[6])
	{
		PosColorUvVertex* outVerticesType = reinterpret_cast<PosColorUvVertex*>(outVertices);

		constexpr static std::array<std::array<float, 2>, 4> dirs{
			std::array<float, 2>{0.f, 0.f},
			std::array<float, 2>{0.f, 1.f},
			std::array<float, 2>{1.f, 1.f},
			std::array<float, 2>{1.f, 0.f}
		};
		for (int i = 0; i < 4; ++i) {
			outVerticesType[i] = PosColorUvVertex{ 
				pos[0] + size[0] * dirs[i][0],
				pos[1] + size[1] * dirs[i][1],
				depth,
				0xFF'FF'FF'FF,
				dirs[i][0],
				dirs[i][1]
			};
		}

		constexpr std::array<uint32_t, 6> indices{ 0, 1, 2, 0, 2, 3};
		bx::memCopy(&outIndices[0], &indices[0], sizeof(indices));
	}
}
