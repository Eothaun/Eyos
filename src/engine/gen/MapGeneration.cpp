#include "engine/gen/MapGeneration.h"
#include "engine/gen/Image.h"
#include "engine/gen/PerlinNoise.h"

#include <sstream>
namespace eyos::gen
{


	MapGeneration::MapGeneration()
	{
		
	}

	MapGeneration::~MapGeneration()
	{
	}

	std::string MapGeneration::GenHeightMap(std::string ImagePath,
		int imageSize,
		double frequency,
		int octaves, 
		std::uint32_t seed
	)
	{
		using namespace  eyos;
		gen::Image image(imageSize,imageSize);

		const gen::PerlinNoise perlin(seed);
		const double fx = image.Width() / frequency;
		const double fy = image.Height() / frequency;

		for (int y = 0; y < image.Height(); ++y)
		{
			for (int x = 0; x < image.Width(); ++x)
			{
				const gen::RGBI color(perlin.octaveNoise0_1(x / fx, y / fy, octaves));

				image.Set(x, y, color);
			}
		}

		std::stringstream ss;

		ss << 'f' << frequency << 'o' << octaves << '_' << seed << ".bmp";
		std::string path = ImagePath;
		path += ss.str();
		if (image.SaveBMP(path.c_str()))
		{
			std::cout << "...saved \"" << ss.str() << "\"\n";
		}
		else
		{
			std::cout << "...failed\n";
			path = "";
		}

		return path;

	}
}