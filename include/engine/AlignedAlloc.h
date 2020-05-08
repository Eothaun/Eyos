#pragma once
// An actual cross platform aligned_alloc solution
// MSVC doesn't implement std::aligned_alloc() so instead you have to use _Aligned_alloc

#ifdef _MSC_VER
#include <malloc.h>
#else
#include <cstdlib>
#endif

namespace eyos
{
	inline void* AlignedMalloc(size_t size, size_t alignment)
	{
#ifdef _MSC_VER
		return _aligned_malloc(size, alignment);
#else
		// Ofc with reversed arguments this time :/ 
		return std::aligned_alloc(alignment, size);
#endif
	}

	inline void* AlignedRealloc(void* block, size_t newSize, size_t alignment)
	{
#ifdef _MSC_VER
		return _aligned_realloc(block, newSize, alignment);
#else
		return std::realloc(block, newSize);
#endif
	}

	inline void AlignedFree(void* block)
	{
#ifdef _MSC_VER
		_aligned_free(block);
#else
		std::free(block);
#endif
	}
}
