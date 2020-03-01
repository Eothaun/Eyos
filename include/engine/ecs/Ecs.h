#pragma once
#include <type_traits>
#include <cassert>
#include <tuple>
#include <array>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <new>

#include <flat.hpp/flat_map.hpp>

#include "EntityId.h"
#include "MTP_Utils.h"
#include "ComponentArray.h"


namespace eyos
{
	namespace ecs_builtins {
		struct EcsTrackable {};

		static_assert(std::is_empty_v<EcsTrackable>, "The ecs depends on this being a 0 size struct");
	}

	//! Generic Ecs class with a compile time switch to enable Tracking of entities
	//! Usually, just use the Alias `Ecs`
	template<bool EcsTrackable>
	class alignas(std::hardware_constructive_interference_size) ConfigurableEcs
	{
	public:
		using ComponentBitset_t = uint16_t;
		static constexpr ComponentBitset_t LastComponentIndex = sizeof(ComponentBitset_t) * 8 - 1;
		static constexpr ComponentBitset_t LastComponentBit = 1 << LastComponentIndex;

		static constexpr bool EcsTrackableEnabled = EcsTrackable;
		// only -1 is an invalid index
		static constexpr int EcsTrackableCmpIndex = EcsTrackableEnabled ? 0 : -1;
		// flags are stored in the far side of the bitmap
		// And Trackable is guaranteed to be the first one flag (if enabled)
		static constexpr ComponentBitset_t EcsTrackableMask = EcsTrackableEnabled ? (1 << (sizeof(ComponentBitset_t) * 8 - 1)) : 0;

		//! Change this variable to a higher variable to allow more components
		static constexpr uint32_t MaxComponentTypes = 16;
		static_assert(MaxComponentTypes <= sizeof(ComponentBitset_t)*8);
		
	public:
		ConfigurableEcs()
		{
			componentTypeToIndex.reserve(MaxComponentTypes);
			if constexpr(EcsTrackableEnabled) {
				RegisterTypes<ecs_builtins::EcsTrackable>();
			}
		}

		flat_hpp::flat_map<TemplateTypeId, uint8_t> componentTypeToIndex{};
		std::array<ComponentArray, MaxComponentTypes> componentArrays{};
		//! The amount of component arrays filled in the `componentArrays` array variable.
		uint8_t componentArrayAmount = 0;
		uint8_t flagTypesAmount = 0;
		
		EntityId::Index_t entityAmount{ 0 };
		//std::tuple<std::vector<TCmps>...> componentTuple{};
		std::vector<ComponentBitset_t> componentBitsets{};
		std::vector<EntityId::Version_t> entityVersions{};
		
		std::unordered_map<EntityId, EntityId::Index_t> sparseToDense{};

		template<typename... Ts>
		void RegisterTypes() {
			(RegisterSingleType<Ts>(),...);
		}

		EntityId CreateEntity()
		{
			++entityAmount;

			//static_for<0, sizeof...(TCmps)>([&](auto i) constexpr {
			//	std::get<i.value>(componentTuple).resize(entityAmount);
			//});
			for (uint32_t i = 0; i < componentArrayAmount; ++i) {
				componentArrays[i].resize_erased(entityAmount);
			}

			componentBitsets.resize(std::max(componentBitsets.size(), static_cast<size_t>(entityAmount)));
			entityVersions.resize(std::max(entityVersions.size(), static_cast<size_t>(entityAmount)));
			assert(componentBitsets.size() == entityVersions.size());
			// If the entity existed before, we increase version to break old handles.
			EntityId::Version_t versionIndex = ++entityVersions[entityAmount - 1];

			return EntityId{ entityAmount - 1, versionIndex };
		}

		void DestroyEntity(EntityId id)
		{
			if constexpr (EcsTrackableEnabled) {
				if (componentBitsets[id.index] & EcsTrackableMask) {
					auto it = sparseToDense.find(id);
					if (it != sparseToDense.end()) {
						sparseToDense.erase(it);
					}
				}
			}

			--entityAmount;

			//Only swap if we are not the last entity
			auto [arrayIndex, valid] = GetIndexInArray(id);
			//TODO: Double check that entityAmount is not off-by-one
			//TODO: Why am I even comparing to entityAmount here??
			if (valid && arrayIndex < entityAmount) {
				if constexpr (EcsTrackableEnabled) {
					if (componentBitsets[entityAmount] & EcsTrackableMask) {
						EntityId lastEntityId{ entityAmount, entityVersions[entityAmount] };
						sparseToDense.insert_or_assign<EntityId::Index_t>(lastEntityId, EntityId::Index_t{ id.index });
					}
				}

				//static_for<0, sizeof...(TCmps)>([&](auto i) constexpr {
				//	auto& componentArray = std::get<i.value>(componentTuple);
				//	std::swap(componentArray[id.index], componentArray[entityAmount]);
				//	});
				for (uint32_t i = 0; i < componentArrayAmount; ++i) {
					auto& componentArray = componentArrays[i];
					componentArray.SwapToEnd(id.index);
				}
				
				std::swap(componentBitsets[id.index], componentBitsets[entityAmount]);
				++entityVersions[id.index];
			}

			//static_for<0, sizeof...(TCmps)>([&](auto i) constexpr {
			//	std::get<i.value>(componentTuple).resize(entityAmount);
			//	});
			for (uint32_t i = 0; i < componentArrays; ++i)
			{
				componentArrays[i].resize_erased(entityAmount);
			}

			// TODO: At the moment this causes a bug, see if we can resize them safely with another technique
			//if constexpr (EcsTrackableEnabled) {
			//	const uint32_t endIndex = componentBitsets.size() - 1;
			//	uint32_t eraseAmount = 0;
			//	for (uint32_t i = endIndex; i >= entityAmount; --i) {
			//		if (!(componentBitsets[i] & EcsTrackableMask)) {
			//			break;
			//		}
			//		++eraseAmount;
			//	}
			//	componentBitsets.resize(endIndex - eraseAmount);
			//	entityVersions.resize(endIndex - eraseAmount);
			//}
			//else {
			//	componentBitsets.resize(entityAmount);
			//	entityVersions.resize(entityAmount);
			//}
		}

		template<typename T>
		void Assign(EntityId id)
		{
			auto [arrayIndex, valid] = GetIndexInArray(id);
			assert(valid);
			if (!valid) {
				return;
			}

			if constexpr (std::is_empty_v<std::decay_t<T>>) {
				componentBitsets[arrayIndex] |= CreateBitsetFromTypes<T>();
			}
			else
			{
				Assign<T>(id, T{});
			}
		}

		template<typename T>
		void Assign(EntityId id, T&& cmp)
		{
			auto [arrayIndex, valid] = GetIndexInArray(id);
			assert(valid);
			if (!valid) {
				return;
			}

			if constexpr (!std::is_empty_v<std::decay_t<T>>) {
				auto it = componentTypeToIndex.find(GetTemplateTypeId<T>());
				if (it != componentTypeToIndex.end()) {
					uint8_t cmpIndex = it->second;

					auto& cmpArray = componentArrays[cmpIndex];
					cmpArray.at<T>(arrayIndex) = std::forward<T>(cmp);
				}
			}

			componentBitsets[arrayIndex] |= CreateBitsetFromTypes<T>();
		}

		template<typename T>
		[[nodiscard]] bool IsValid(EntityId id) const
		{
			if (id.index < entityAmount) {
				//TODO: If this returns false, it should still check if we are EcsTrackable right?
				return id.version == entityVersions[id.index];
			}
			if constexpr (EcsTrackableEnabled) {
				if (componentBitsets[id.index] & EcsTrackableMask) {
					return sparseToDense.find(id) != sparseToDense.end();
				}
			}

			return false;
		}

		template<typename T>
		void Remove(EntityId id)
		{
			auto [arrayIndex, valid] = GetIndexInArray(id);
			assert(valid);

			if constexpr (!std::is_empty_v<std::decay_t<T>>) {
				//TODO: Do we want this to happen in release too?
#ifdef _DEBUG
				auto it = componentTypeToIndex.find(GetTemplateTypeId<T>());
				if (it != componentTypeToIndex.end()) {
					uint8_t cmpIndex = *it;

					auto& cmpArray = componentArrays[cmpIndex];
					cmpArray.at<T>(arrayIndex) = T{};
				}
#endif
			}

			componentBitsets[arrayIndex] &= ~CreateBitsetFromTypes<T>();

			if constexpr (std::is_same_v<std::decay_t<T>, ecs_builtins::EcsTrackable>) {
				auto it = sparseToDense.find(id);
				if (it != sparseToDense.end()) {
					sparseToDense.erase(it);
				}
			}
		}

		template<typename T>
		[[nodiscard]] T& Get(EntityId id)
		{
			auto it = componentTypeToIndex.find(GetTemplateTypeId<T>());
			if (it != componentTypeToIndex.end()) {
				uint8_t cmpIndex = it->second;

				auto [arrayIndex, valid] = GetIndexInArray(id);
				assert(valid);

				auto& cmpArray = componentArrays[cmpIndex];
				return cmpArray.at<T>(arrayIndex);
			}
			// TODO: Make a proper macro for this, named something like `UNREACHABLE()` like in rust
			assert(false);
			std::abort();
		}

		//TODO: Make a overload which takes a buffer instead of allocating all the time
		//! \Note: The vector of Entities will reserve a length of all entities. If memory is an issue, consider calling .shrink_to_fit()
		template<typename... Ts>
		[[nodiscard]] std::vector<EntityId> QueryEntities()
		{
			std::vector<EntityId> entities;
			//TODO: Reconsider this. its quite aggressive, but most performant. And .shrink_to_fit() can be called by the user later.
			entities.reserve(entityAmount);

			ComponentBitset_t componentMask = CreateBitsetFromTypes<Ts...>();
			for (EntityId::Index_t i = 0; i < entityAmount; ++i) {
				if ((componentBitsets[i] & componentMask) == componentMask) {
					entities.push_back(EntityId{ i, entityVersions[i] });
				}
			}

			return entities;
		}

	private:
		//! An id is usually just the index, but can also be redirected if the ecs and entity is EcsTrackable.
		//! This function will also indicate if the index is valid
		//! \NOTE If valid is `false`, then the index value is undefined.
		std::pair<EntityId::Index_t, bool> GetIndexInArray(EntityId id)
		{
			if constexpr (EcsTrackableEnabled) {
				if (id.index < entityAmount) {
					if (id.version == entityVersions[id.index]) {
						return { EntityId::Index_t{ id.index }, true };
					}
				}
				if (id.index < entityVersions.size()) {
					if (entityVersions[id.index] & EcsTrackableMask) {
						auto it = sparseToDense.find(id);
						if (it != sparseToDense.end()) {
							return { it->second, true };
						}
					}
					return { EntityId::InvalidIndex, false };
				}
				else {
					return { EntityId::InvalidIndex, false };
				}
			}
			else {
				return { id.index, id.version == entityVersions[id.index] };
			}
		}

		template<typename... Ts>
		ComponentBitset_t CreateBitsetFromTypes()
		{
			return (GetBitInBitsetFromType<Ts>() | ...);
		}

		template<typename T>
		ComponentBitset_t GetBitInBitsetFromType()
		{
			auto index = componentTypeToIndex.at(GetTemplateTypeId<T>());
			return 1 << index;
		}
		
		template<typename T>
		void RegisterSingleType()
		{
			assert(componentArrayAmount + flagTypesAmount < MaxComponentTypes && "The maximum amount of component types has been exceeded");
			if (componentArrayAmount + flagTypesAmount >= MaxComponentTypes) {
				return;
			}
			
			if constexpr (std::is_empty_v<T>)
			{
				auto currentIndex = flagTypesAmount++;
				// flags are stored from the end of the bitmask, so that the index for data components aligns in the componentArray
				componentTypeToIndex[GetTemplateTypeId<T>()] = LastComponentIndex - currentIndex;
			}
			else
			{
				auto currentChunk = componentArrayAmount++;

				componentArrays[currentChunk] = ComponentArray::CreateFromType<T>();
				assert(componentTypeToIndex.find(GetTemplateTypeId<T>()) == componentTypeToIndex.end()
					&& "Component array of type T is already created before!");
				componentTypeToIndex[GetTemplateTypeId<T>()] = currentChunk;
			}
		}
	};

	//! Default implementation of the ECS, has entity tracking enabled. Because it is useful 90% of the time
	using Ecs = ConfigurableEcs<true>;
	//! For the 10% of the time when persistent entity tracking is not required. Some branches can be avoided
	using EcsWithoutTracking = ConfigurableEcs<true>;
}
