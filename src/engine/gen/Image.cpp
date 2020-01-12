#include "engine/gen/Image.h"

namespace eyos::gen
{
	bool Image::InBounds(std::int32_t y, std::int32_t x) const noexcept
	{
		return (0 <= y) && (y < height) && (0 <= x) && (x < width);
	}

	constexpr std::uint8_t Image::ToUint8(double x) noexcept
	{
		return x >= 1.0 ? 255 : x <= 0.0 ? 0 : static_cast<std::uint8_t>(x * 255.0 + 0.5);
	}

	void Image::Set(std::int32_t x, std::int32_t y, const RGBI& color)
	{
		if (!InBounds(y, x))
		{
			return;
		}

		data[y * (unsigned __int64)width + x] = color;
	}

	bool Image::SaveBMP(const std::string& path)
	{
		const std::int32_t  rowSize = width * 3 + width % 4;
		const std::uint32_t bmpsize = rowSize * height;
		const BMPHeader	header =
		{
			0x4d42,
			static_cast<std::uint32_t>(bmpsize + sizeof(BMPHeader)),
			0,
			0,
			sizeof(BMPHeader),
			40,
			width,
			height,
			1,
			24,
			0,
			bmpsize,
			0,
			0,
			0,
			0
		};

		if (std::ofstream ofs{ path, std::ios_base::binary })
		{
			ofs.write((const char*)&header, sizeof(header));

			std::vector<std::uint8_t> line(rowSize);

			for (std::int32_t y = height - 1; -1 < y; --y)
			{
				size_t pos = 0;

				for (std::int32_t x = 0; x < width; ++x)
				{
					const RGBI& col = data[y * (unsigned __int64)width + x];
					line[pos++] = ToUint8(col.b);
					line[pos++] = ToUint8(col.g);
					line[pos++] = ToUint8(col.r);
				}
				fLine = line;
				size = static_cast<std::uint32_t>(bmpsize + sizeof(BMPHeader));
				ofs.write((const char*)line.data(), line.size());
			}

			

			return true;
		}
		else
		{
			return false;
		}
	}
}