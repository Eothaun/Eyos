#pragma once
#include <cstdint>
#include <memory>
#include <cstdlib>

#include "MTP_Utils.h"


namespace eyos 
{
	template<typename T>
	struct AlignedDeleter
	{
		void operator()(T* t)
		{
			_aligned_free(t);
		}
	};
	
	//! A type erased component array
	//! Funnily enough this struct feels a lot like a memory allocator
	class ComponentArray
	{
	public:
		using ErasedConstructor = void(*)(void* ptr);
		using ErasedDeconstructor = void(*)(void* ptr);
		using ErasedMoveAssignment = void(*)(void* to, void* from);
		using ErasedSwap = void(*)(void* a, void* b);

	private:
		//TODO: Make sure we allocate from and with the correct alignment
		std::unique_ptr<std::byte[], AlignedDeleter<std::byte[]>> data{};
		uint32_t elementCount = 0;
		uint32_t elementCapacity = 0;
		
		TemplateTypeId typeId = g_invalidTemplateTypeId;
		size_t alignment = alignof(max_align_t);
		uint32_t componentSize = 0;
		ErasedConstructor componentConstructor = nullptr;
		ErasedDeconstructor componentDeconstructor = nullptr;
		ErasedMoveAssignment componentMoveAssign = nullptr;
		ErasedSwap componentSwap = nullptr;
		bool isTrivial = false;

	public:
		ComponentArray() = default;
		~ComponentArray();

		// Copying can be slow (T is not trivial) and I don't see a use for this yet. So I haven't implemented it
		// Though it should be fairly easy to implement should it be required in the future
		ComponentArray(const ComponentArray& other) = delete;
		ComponentArray(ComponentArray&& other) noexcept; // NOLINT(bugprone-exception-escape)
		// Copying can be slow (T is not trivial) and I don't see a use for this yet. So I haven't implemented it
		// Though it should be fairly easy to implement should it be required in the future
		ComponentArray& operator=(const ComponentArray& other) = delete;
		ComponentArray& operator=(ComponentArray&& other) noexcept; // NOLINT(bugprone-exception-escape)

		template<typename T>
		static ComponentArray CreateFromType();

		[[nodiscard]] uint32_t size() const
		{
			return elementCount;
		}
		[[nodiscard]] uint32_t capacity() const
		{
			return elementCapacity;
		}

		//! \NOTE newSize is in amount of elements. NOT in amount of bytes
		void resize_erased(uint32_t newSize)
		{
			if (capacity() < newSize)
			{
				std::byte* biggerArr = static_cast<std::byte*>( _aligned_malloc(newSize * componentSize, alignment) );
				if(isTrivial)
				{
					memcpy(biggerArr, data.get(), size() * componentSize);
				}
				else
				{
					for (uint32_t i = 0; i < size(); ++i)
					{
						componentMoveAssign(&biggerArr[i*componentSize], at_erased(i));
					}
				}
				data.reset(biggerArr);
			}

			elementCount = newSize;
		}

		//! Overload of resize which takes the type, which means the compiler can inline the move constructor
		template<typename T>
		void resize(uint32_t newSize)
		{
			// Ahm this looks like UB waiting to happen. But lets see if it works
			std::vector<T>& elementVec = reinterpret_cast<std::vector<T>&>(data);

			elementVec.resize(newSize);
		}

		void* at_erased(uint32_t index)
		{
			size_t byteIndex = static_cast<size_t>(index) * componentSize;
			return &data[byteIndex];
		}

		template<typename T>
		T & at(uint32_t index)
		{
			//Sanity check
			assert(sizeof(T) == componentSize);

			size_t byteIndex = static_cast<size_t>(index) * componentSize;
			return reinterpret_cast<T&>(data[byteIndex]);
		}

		//! Get the last element in the array
		void* back_erased()
		{
			return at_erased(size()-1);
		}

		template<typename T>
		T& back()
		{
			return reinterpret_cast<T&>( back_erased() );
		}

		void SwapToEnd(uint32_t index)
		{
			//TODO: I could check for isTrivial and then do something like alloca() memcpy the bytes, and swap like that. But I kinda doubt it would be faster.
			componentSwap(at_erased(index), back_erased());
		}

		void SwapElements(uint32_t indexA, uint32_t indexB)
		{
			componentSwap(at_erased(indexA), at_erased(indexB));
		}

	private:
		void Destroy();
	};

	inline ComponentArray::~ComponentArray()
	{
		Destroy();
	}


	inline ComponentArray::ComponentArray(ComponentArray&& other) noexcept // NOLINT(bugprone-exception-escape)
	{
		Destroy();

		elementCount = other.elementCount;
		elementCapacity = other.elementCapacity;
		typeId = other.typeId;
		alignment = other.alignment;
		componentSize = other.componentSize;
		componentConstructor = other.componentConstructor;
		componentDeconstructor = other.componentDeconstructor;
		componentMoveAssign = other.componentMoveAssign;
		componentSwap = other.componentSwap;
		isTrivial = other.isTrivial;
		
		if(isTrivial)
		{
			data = std::move(other.data);
		}
		else
		{
			data.reset(static_cast<std::byte*>( _aligned_malloc(elementCount * componentSize, alignment) ));
			for(uint32_t i = 0; i < size(); ++i)
			{
				componentMoveAssign(at_erased(i), other.at_erased(i));
			}
		}
	}

	inline ComponentArray& ComponentArray::operator=(ComponentArray&& other) noexcept // NOLINT(bugprone-exception-escape)
	{
		if (this == &other)
			return *this;

		Destroy();
		
		typeId = other.typeId;
		alignment = other.alignment;
		componentSize = other.componentSize;
		componentConstructor = other.componentConstructor;
		componentDeconstructor = other.componentDeconstructor;
		componentMoveAssign = other.componentMoveAssign;
		componentSwap = other.componentSwap;
		isTrivial = other.isTrivial;

		if(isTrivial)
		{
			data = std::move(other.data);
		}
		else
		{
			data.reset(static_cast<std::byte*>( _aligned_malloc(elementCount * componentSize, alignment) ));
			for(uint32_t i = 0; i < size(); ++i)
			{
				componentMoveAssign(at_erased(i), other.at_erased(i));
			}
		}
		
		return *this;
	}

	inline void ComponentArray::Destroy()
	{
		if(!isTrivial){
			for(uint32_t i = 0; i < elementCount; ++i)
			{
				componentDeconstructor(at_erased(i));
			}
		}
		data.reset();
	}


	template <typename T>
	ComponentArray ComponentArray::CreateFromType()
	{
		ComponentArray compArray{};
		compArray.typeId = GetTemplateTypeId<T>();
		compArray.alignment = alignof(T);
		compArray.componentSize = sizeof(T);
		compArray.componentConstructor = &ConstructThing<T>;
		compArray.componentDeconstructor = &DeconstructThing<T>;
		compArray.componentMoveAssign = &MoveThing<T>;
		compArray.componentSwap = &SwapThings<T, T>;
		compArray.isTrivial = std::is_trivial_v<T>;

		return compArray;
	}
}