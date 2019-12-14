#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <cstdint>

#include "bgfx_utils.h"
#include "font/font_manager.h"
#include "font/text_buffer_manager.h"


namespace eyos {
	class UIRenderer;

	namespace UI {
		class Widget {
		public:
			virtual ~Widget() = 0;

		protected:
			Widget() = default;
			Widget(float pos[2], float size[2], float depth = 0) 
				: pos{ pos[0], pos[1] }, size{ size[0], size[1] }, depth(depth) {}

		public:
			float pos[2];
			float size[2];
			float depth;
		};

		class ImageWidget : public Widget {
		public:
			~ImageWidget() = default;

		protected:
			friend UIRenderer;
			ImageWidget() = default;
			ImageWidget(float pos[2], float size[2], float depth, bgfx::TextureHandle texture)
				: Widget(pos, size, depth), texture(texture) {}
		
		public:
			bgfx::TextureHandle texture;
		};

		class TextWidget : public Widget {
		public:
			~TextWidget() = default;

		protected:
			friend UIRenderer;
			TextWidget() = default;
			TextWidget(float pos[2], float size[2], float depth, std::string text, bgfx::TextureHandle textTexture)
				: Widget(pos, size, depth), text(std::move(text)), textTexture(textTexture) {}

		public:
			std::string text;
			bgfx::TextureHandle textTexture;
		};
	}
	
	class UIRenderer {
	public:
		UIRenderer(uint32_t width, uint32_t height);
		~UIRenderer();

		UI::ImageWidget* CreateImageWidget(float pos[2], float size[2], float depth, bgfx::TextureHandle texture);
		UI::TextWidget* CreateTextWidget(float pos[2], float size[2], float depth, std::string_view text);
		void DestoyImageWidget(UI::ImageWidget* imageWidget);
		void DestoyTextWidget(UI::TextWidget* textWidget);

		void ClearAll();

		void Render();

		void OnResolutionChanged(uint32_t newWidth, uint32_t newHeight);

	private:
		void GenerateQuad(float pos[2], float size[2], float depth, void* outVertices, uint32_t outIndices[6]);

	private:
		std::vector<std::unique_ptr<UI::ImageWidget>> imageWidgets;
		std::vector<std::unique_ptr<UI::TextWidget>> textWidgets;

		bgfx::DynamicVertexBufferHandle vtxBufferHandle;
		bgfx::DynamicIndexBufferHandle idxBufferHandle;

		bgfx::ProgramHandle shaderProgram;
		bgfx::UniformHandle textureUniform;
		uint32_t screenWidth, screenHeight;

		FontHandle fontHandle;
		TrueTypeHandle ttfHandle;
		TextBufferHandle transientTextBuffer;
		std::unique_ptr<FontManager> fontManager;
		std::unique_ptr<TextBufferManager> textBufferManager;
	};
}