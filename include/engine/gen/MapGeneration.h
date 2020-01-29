#pragma once
#include <iostream>
#include "engine/Defines.hpp"

namespace eyos::gen
{

	static class EYOS_API MapGeneration
	{
	public:
		MapGeneration();
		~MapGeneration();

		static std::string GenHeightMap(std::string ImagePath,
			int imageSize = 512,
			double frequency = 2.0, 
			int octaves = 2, 
			std::uint32_t seed = 2
		);

	private:

	};

}