#include "engine/gen/PerlinNoise.h"


namespace eyos::gen
{

	double PerlinNoise::Fade(double t) noexcept
	{
		return t * t * t * (t * (t * 6 - 15) + 10);
	}

	double PerlinNoise::Lerp(double t, double a, double b) noexcept
	{
		return a + t * (b - a);
	}

	double PerlinNoise::Grad(std::uint8_t hash, double x, double y, double z) noexcept
	{
		const std::uint8_t h = hash & 15;
		const double u = h < 8 ? x : y;
		const double v = h < 4 ? y : h == 12 || h == 14 ? x : z;
		return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
	}



	void PerlinNoise::reseed(std::uint32_t seed)
	{
		for (size_t i = 0; i < 256; ++i)
		{
			p[i] = static_cast<std::uint8_t>(i);
		}

		std::shuffle(std::begin(p), std::begin(p) + 256, std::default_random_engine(seed));

		for (size_t i = 0; i < 256; ++i)
		{
			p[256 + i] = p[i];
		}
	}

	double PerlinNoise::noise(double x, double y, double z) const
	{
		const std::int32_t X = static_cast<std::int32_t>(std::floor(x)) & 255;
		const std::int32_t Y = static_cast<std::int32_t>(std::floor(y)) & 255;
		const std::int32_t Z = static_cast<std::int32_t>(std::floor(z)) & 255;

		x -= std::floor(x);
		y -= std::floor(y);
		z -= std::floor(z);

		const double u = Fade(x);
		const double v = Fade(y);
		const double w = Fade(z);

		const std::int32_t A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z;
		const std::int32_t B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;

		return Lerp(w, Lerp(v, Lerp(u, Grad(p[AA], x, y, z),
			Grad(p[BA], x - 1, y, z)),
			Lerp(u, Grad(p[AB], x, y - 1, z),
				Grad(p[BB], x - 1, y - 1, z))),
			Lerp(v, Lerp(u, Grad(p[AA + 1], x, y, z - 1),
				Grad(p[BA + 1], x - 1, y, z - 1)),
				Lerp(u, Grad(p[AB + 1], x, y - 1, z - 1),
					Grad(p[BB + 1], x - 1, y - 1, z - 1))));
	}

	double PerlinNoise::octaveNoise(double x, std::int32_t octaves) const
	{
		double result = 0.0;
		double amp = 1.0;

		for (std::int32_t i = 0; i < octaves; ++i)
		{
			result += noise(x) * amp;
			x *= 2.0;
			amp *= 0.5;
		}

		return result;
	}

	double PerlinNoise::octaveNoise(double x, double y, std::int32_t octaves) const
	{
		double result = 0.0;
		double amp = 1.0;

		for (std::int32_t i = 0; i < octaves; ++i)
		{
			result += noise(x, y) * amp;
			x *= 2.0;
			y *= 2.0;
			amp *= 0.5;
		}

		return result;
	}

	double PerlinNoise::octaveNoise(double x, double y, double z, std::int32_t octaves) const
	{
		double result = 0.0;
		double amp = 1.0;

		for (std::int32_t i = 0; i < octaves; ++i)
		{
			result += noise(x, y, z) * amp;
			x *= 2.0;
			y *= 2.0;
			z *= 2.0;
			amp *= 0.5;
		}

		return result;
	}

}