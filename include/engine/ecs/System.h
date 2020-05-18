#pragma once
#include <engine/ecs/MTP_Utils.h>

#include <cstdint>
#include <tuple>
#include <vector>

#include "Ecs.h"
#include "EntityId.h"

namespace eyos
{
	template<typename... TCmps>
	struct ComponentQueryIterator;

	template<typename... TCmps>
	struct ComponentQuery;
}

namespace std
{
	//template <typename... TCmps>
	//struct iterator_traits< eyos::ComponentQueryIterator<TCmps...>>{
	//	using iterator_category = std::random_access_iterator_tag;
	//	using value_type = std::tuple<TCmps...>;
	//	using difference_type = std::ptrdiff_t;
	//	using pointer = std::tuple<TCmps...>*;
	//	using reference = std::tuple<TCmps...>&;
	//};
}

namespace eyos
{
	class World;

	//TODO: Make a const variant
	template<typename... TCmps>
	struct ComponentQueryIterator
	{
		using iterator_category = std::random_access_iterator_tag;
		using value_type = std::tuple<TCmps..., EntityId>;
		using difference_type = std::ptrdiff_t;
		using pointer = value_type*;
		using reference = value_type&;
		
		ComponentQuery<TCmps...>* query = nullptr;
		EntityId::Index_t index = EntityId::InvalidIndex;

		//ComponentQueryIterator() = default;
		//ComponentQueryIterator()

		friend bool operator==(const ComponentQueryIterator& lhs, const ComponentQueryIterator& rhs)
		{
			return lhs.query == rhs.query
				&& lhs.index == rhs.index;
		}

		friend bool operator!=(const ComponentQueryIterator& lhs, const ComponentQueryIterator& rhs)
		{
			return !(lhs == rhs);
		}

		friend bool operator<(const ComponentQueryIterator& lhs, const ComponentQueryIterator& rhs)
		{
			return lhs.index < rhs.index;
		}

		friend bool operator<=(const ComponentQueryIterator& lhs, const ComponentQueryIterator& rhs)
		{
			return !(rhs < lhs);
		}

		friend bool operator>(const ComponentQueryIterator& lhs, const ComponentQueryIterator& rhs)
		{
			return rhs < lhs;
		}

		friend bool operator>=(const ComponentQueryIterator& lhs, const ComponentQueryIterator& rhs)
		{
			return !(lhs < rhs);
		}

		ComponentQueryIterator& operator++()
		{
			++index;
			return *this;
		}

		ComponentQueryIterator operator++(int)
		{
			auto oldIndex = index++;
			return ComponentQuery{ this, oldIndex };
		}
		
		ComponentQueryIterator& operator--()
		{
			--index;
			return *this;
		}

		ComponentQueryIterator operator--(int)
		{
			auto oldIndex = index--;
			return ComponentQuery{ this, oldIndex };
		}

		friend ComponentQueryIterator operator+(const ComponentQueryIterator& lhs, uint32_t n)
		{
			return { lhs.query, lhs.index + n };
		}
		friend ComponentQueryIterator operator-(const ComponentQueryIterator& lhs, uint32_t n)
		{
			return { lhs.query, lhs.index - n };
		}
		ComponentQueryIterator& operator+=(uint32_t n)
		{
			index += n;

			return *this;
		}
		ComponentQueryIterator& operator-=(uint32_t n)
		{
			index -= n;

			return *this;
		}

		void FillTuple(reference tuple, uint32_t n = 0);

		//value_type operator[](uint32_t n) {
		//	value_type cmps;

		//	FillTuple(cmps, n);

		//	return cmps;
		//}
		template<typename T>
		T GetElement(uint32_t index_param)
		{
			constexpr auto cmpIndex = get_index_in_pack<T, TCmps...>;
			static_assert(cmpIndex != -1);
			return std::forward<T>(std::get<cmpIndex>(query->componentArrays)[index_param]);
		}
		value_type operator*()
		{
			value_type cmps{GetElement<TCmps>(index)..., query->entityIds[index]};

			//FillTuple(cmps);

			return cmps;
		}
	};

	template<typename... TCmps>
	struct ComponentQuery
	{
		using iterator = ComponentQueryIterator<TCmps...>;
		
		std::tuple<std::vector<MakeRefARefWrapper_t<TCmps>>...> componentArrays;
		std::vector<EntityId> entityIds;

		[[nodiscard]] auto begin()
		{
			return iterator{ this, 0 };
		}
		//[[nodiscard]] auto begin() const
		//{
		//	return iterator{ this, 0 };
		//}
		[[nodiscard]] auto end()
		{
			return iterator{ this, static_cast<uint32_t>( std::get<0>(componentArrays).size() ) };
		}
		//[[nodiscard]] auto end() const
		//{
		//	return iterator{ this, std::get<0>(componentArrays).size() };
		//}

		void resize(size_t newSize)
		{
			entityIds.resize(newSize, EntityId{ EntityId::InvalidIndex });

			static_for<0, sizeof...(TCmps)>([&componentArrays, newSize](auto i) constexpr {
				auto& componentArray = std::get<i.value>(componentArrays);
				componentArray.resize(newSize, EntityId{ EntityId::InvalidIndex });
			});
		}
	};

	template<typename... TCmps>
	void FillQuery(ComponentQuery<TCmps...>& query, Ecs& ecs)
	{
		query.entityIds = ecs.QueryEntities<TCmps...>();
		const auto entityAmount = query.entityIds.size();
		query.resize(entityAmount);

		(FillQuerySpecificComponent<TCmps>(query, ecs),...);
	}

	template<typename TCmp, typename... TCmps>
	void FillQuerySpecificComponent(ComponentQuery<TCmps...>& query, Ecs& ecs)
	{
		constexpr auto cmpIndexInQuery = get_index_in_pack<TCmp, TCmps...>;
		static_assert(cmpIndexInQuery != -1, "Type TCmp is not found in the query!");
		auto& componentArray = std::get<cmpIndexInQuery>(query.componentArrays);

		const auto entityAmount = query.entityIds.size();		
		for(int i = 0; i < entityAmount; ++i)
		{
			//TODO: Make references work
			componentArray[i] = make_ref_a_ref_wrapper( ecs.Get<TCmp>(query.entityIds[i]) );
		}
	}
	
	class ISystem
	{
	public:
		ISystem(TemplateTypeId derivedTypeId) : derivedTypeId(derivedTypeId) {}
		virtual ~ISystem() = default;

		ISystem(const ISystem& other) = delete;
		ISystem(ISystem&& other) noexcept = default;
		ISystem& operator=(const ISystem& other) = delete;
		ISystem& operator=(ISystem&& other) noexcept = default;
		
		virtual void Init(World& world) = 0;
		virtual void UpdateWithWorld(World& entities) = 0;
		virtual void Shutdown() = 0;

		[[nodiscard]] TemplateTypeId GetDerivedTypeId() const { return derivedTypeId; }
		
	private:
		const TemplateTypeId derivedTypeId;
	};

	template<typename T>
	struct SystemThings
	{
		// Default query is nothing
		using Query = Types<>;
		// By default, no dependencies on other systems
		using Dependencies = Types<>;
	};

	template<template<typename...> typename TTarget>
	struct ConvertTypesTo
	{
	public:
		template<typename... TArgs>
		constexpr static TTarget<TArgs...> FromFunc(Types<TArgs...>)
		{
			return std::declval < TTarget<TArgs...> >();
		}

		template<typename T>
		using From = decltype(FromFunc(T{}));
	};

	template<typename TDerived>
	class System : public ISystem
	{
	public:
		using SystemComponentQuery = ConvertTypesTo<ComponentQuery>::From<typename SystemThings<TDerived>::Query>;
		
	public:
		System() : ISystem(GetTemplateTypeId<TDerived>()) {}

		using ISystem::Init;
		using ISystem::Shutdown;

		void UpdateWithWorld(World& entities) override final;
	};

	template <typename ... TCmps>
	void ComponentQueryIterator<TCmps...>::FillTuple(reference tuple, uint32_t n)
	{
		auto furtherIndex = index + n;
		static_for<0, sizeof...(TCmps)>([&tuple, query, furtherIndex](auto i) constexpr {
			auto& componentArray = std::get<i.value>(query->componentArrays);
			std::get<i.value>(tuple) = componentArray[furtherIndex];
		});
		//std::get<sizeof...(TCmps) + 1>(tuple) = query->entityIds[furtherIndex];
	}

	template <typename TDerived>
	void System<TDerived>::UpdateWithWorld(World& world)
	{
		static_assert(std::is_base_of_v<System<TDerived>, TDerived>, "The CRTP needs to be the system which inherits from `System<Itself>`");

		SystemComponentQuery query{};
		FillQuery(query, world);

		//TODO: This is not really safe right? how can I test this
		reinterpret_cast<TDerived*>(this)->Update((query));
	}

	class SystemScheduler
	{
	private:
		std::vector<std::unique_ptr<ISystem>> systems;
		std::vector<ISystem*> needsInitializing;
		
	public:
		template<typename T>
		T* AddSystem(T&& t)
		{
			static_assert(std::is_base_of_v<ISystem, T>);
			
			T* tPtr = new T(std::forward<T>(t));
			auto& uniquePtr = systems.emplace_back(tPtr);
			needsInitializing.push_back(tPtr);
			return tPtr;
		}

		void UpdateAll(World& world)
		{
			for (ISystem* system : needsInitializing) {
				system->Init(world);
			}
			needsInitializing.clear();

			for (auto& system : systems) {
				system->UpdateWithWorld(world);
			}
		}

		//! \NOTE During this function, parameter t will be deleted. As the scheduler owns the systems
		template<typename T>
		void DestroySystem(T* t)
		{
			static_assert(std::is_base_of_v<ISystem, T>);
			
			//Remove from needsInitializing
			{
				auto it = std::find(needsInitializing.begin(), needsInitializing.end(), t);
				if (it != needsInitializing.end()) {
					// Order is important, so we cannot swap to the end.
					needsInitializing.erase(it);
				}
			}
			
			//Remove from systems, which will destroy itself
			{
				auto it = std::find_if(systems.begin(), systems.end(), [t](std::unique_ptr<ISystem>& systemPtr) { return systemPtr.get() == t; });
				if(it != systems.end()) {
					// Order is important, so we cannot swap to the end.
					systems.erase(it);
				}
			}
		}
	};
}
