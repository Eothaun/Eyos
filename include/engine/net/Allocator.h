#include "engine/Defines.h"
#include <cstddef>
namespace eyos::net {
	class EYOS_API Allocator {
	public:
		Allocator() = default;
		Allocator(const Allocator&) = delete;
		Allocator(Allocator&&) = delete;
		Allocator& operator=(const Allocator&) = delete;
		Allocator& operator=(Allocator&&) = delete;
		~Allocator();
		bool Init([[maybe_unused]] std::size_t bufferSize);
		void* Allocate(std::size_t size);
		void Free(void* ptr);
	private:
		[[maybe_unused]] std::byte* buffer{};
		[[maybe_unused]] std::size_t chunckSize{};
		[[maybe_unused]] bool inited{false};
	};
	EYOS_API Allocator& GetNetworkAllocator();
}