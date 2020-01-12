#pragma once

#include "engine/Defines.hpp"

#include <cstdint>
#include <numeric>
#include <algorithm>
#include <random>
#include <iterator>
#include <type_traits>
#include <vector>

namespace eyos::gen
{
	class EYOS_API PerlinNoise
	{
		PerlinNoise() = default;
	private:
		std::uint8_t p[512];
		static double Fade(double t) noexcept;
		static double Lerp(double t, double a, double b) noexcept;
		static double Grad(std::uint8_t hash, double x, double y, double z) noexcept;

	public:
		explicit PerlinNoise(std::uint32_t seed = std::default_random_engine::default_seed)
		{
			reseed(seed);
		}

		//template <class URNG, std::enable_if_t<!std::is_arithmetic_v<URNG>> * = nullptr>
		//explicit PerlinNoise(URNG& urng)
		//{
		//	reseed(urng);
		//}

		void reseed(std::uint32_t seed);

		//template <class URNG, std::enable_if_t<!std::is_arithmetic_v<URNG>> * = nullptr>
		//void reseed(URNG& urng)
		//{
		//	for (size_t i = 0; i < 256; ++i)
		//	{
		//		p[i] = static_cast<std::uint8_t>(i);
		//	}
		//
		//	std::shuffle(std::begin(p), std::begin(p) + 256, urng);
		//
		//	for (size_t i = 0; i < 256; ++i)
		//	{
		//		p[256 + i] = p[i];
		//	}
		//}

		double noise(double x) const { return noise(x, 0.0, 0.0); }
		double noise(double x, double y) const{ return noise(x, y, 0.0); }
		double noise(double x, double y, double z) const;

		double octaveNoise(double x, std::int32_t octaves) const;
		double octaveNoise(double x, double y, std::int32_t octaves) const;
		double octaveNoise(double x, double y, double z, std::int32_t octaves) const;

		double noise0_1(double x) const { return noise(x) * 0.5 + 0.5; };
		double noise0_1(double x, double y) const { return noise(x, y) * 0.5 + 0.5; };
		double noise0_1(double x, double y, double z) const { return noise(x, y, z) * 0.5 + 0.5; };

		double octaveNoise0_1(double x, std::int32_t octaves) const { return octaveNoise(x, octaves) * 0.5 + 0.5; }
		double octaveNoise0_1(double x, double y, std::int32_t octaves) const { return octaveNoise(x, y, octaves) * 0.5 + 0.5; }
		double octaveNoise0_1(double x, double y, double z, std::int32_t octaves) const { return octaveNoise(x, y, z, octaves) * 0.5 + 0.5; };
	};


}