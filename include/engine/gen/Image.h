#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include "engine/Defines.hpp"
namespace eyos::gen
{
# pragma pack (push, 1)
	struct BMPHeader
	{
		std::uint16_t bfType;
		std::uint32_t bfSize;
		std::uint16_t bfReserved1;
		std::uint16_t bfReserved2;
		std::uint32_t bfOffBits;
		std::uint32_t biSize;
		std::int32_t  biWidth;
		std::int32_t  biHeight;
		std::uint16_t biPlanes;
		std::uint16_t biBitCount;
		std::uint32_t biCompression;
		std::uint32_t biSizeImage;
		std::int32_t  biXPelsPerMeter;
		std::int32_t  biYPelsPerMeter;
		std::uint32_t biClrUsed;
		std::uint32_t biClrImportant;
	};

	static_assert(sizeof(BMPHeader) == 54);
# pragma pack (pop)

	struct RGBI
	{
		double r = 0.0;
		double g = 0.0;
		double b = 0.0;
		RGBI() = default;
		explicit constexpr RGBI(double _rgb) noexcept
			: r(_rgb), g(_rgb), b(_rgb) {}
		constexpr RGBI(double _r, double _g, double _b) noexcept
			: r(_r), g(_g), b(_b) {}
	};

	class EYOS_API Image
	{
	private:
		std::vector<RGBI> data;
		std::int32_t width = 0;
		std::int32_t height = 0;

		

		bool InBounds(std::int32_t y, std::int32_t x) const noexcept;
		static constexpr std::uint8_t ToUint8(double x) noexcept;

	public:
		std::vector<std::uint8_t> fLine;
		std::uint32_t size;

		Image() = default;
		Image(std::int32_t width, std::int32_t height)
			: data((unsigned __int64)width * (unsigned __int64)height)
			, width(width)
			, height(height) {}

		void Set(std::int32_t x, std::int32_t y, const RGBI& color);

		int Width() const { return width; };
		int Height() const { return height; };

		bool SaveBMP(const std::string& path);
	};
}