#pragma once
#include <type_traits>
#include <cassert>
#include <tuple>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "EntityId.h"
#include "MTP_Utils.h"


namespace eyos
{
	namespace ecs_builtins {
		struct EcsTrackable {};

		static_assert(std::is_empty_v<EcsTrackable>, "The ecs depends on this being a 0 size struct");
	}

	template<typename... TCmps>
	class Ecs
	{
		static_assert(sizeof...(TCmps) <= 16, "For now, our amount of components has to fit in a uint16_t");

	public:
		static constexpr int EcsTrackableCmpIndex = get_index_in_pack<ecs_builtins::EcsTrackable, TCmps...>;
		static constexpr bool EcsTrackableEnabled = EcsTrackableCmpIndex != -1;
		static constexpr uint16_t EcsTrackableMask = EcsTrackableEnabled ? (1 << EcsTrackableCmpIndex) : 0;

	public:
		Ecs() = default;

		EntityId::Index_t entityAmount{};
		std::tuple<std::vector<TCmps>...> componentTuple{};
		std::vector<uint16_t> componentBitsets{};
		std::vector<EntityId::Version_t> entityVersions{};
		std::unordered_map<EntityId, EntityId::Index_t> sparseToDense{};

		EntityId CreateEntity()
		{
			++entityAmount;

			static_for<0, sizeof...(TCmps)>([&](auto i) constexpr {
				std::get<i.value>(componentTuple).resize(entityAmount);
				});
			componentBitsets.resize(std::max(componentBitsets.size(), static_cast<size_t>(entityAmount)));
			entityVersions.resize(std::max(entityVersions.size(), static_cast<size_t>(entityAmount)));
			assert(componentBitsets.size() == entityVersions.size());
			// If the entity existed before, we increase version to break old handle.
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
			if (valid && arrayIndex < entityAmount) {
				if constexpr (EcsTrackableEnabled) {
					if (componentBitsets[entityAmount] & EcsTrackableMask) {
						EntityId lastEntityId{ entityAmount, entityVersions[entityAmount] };
						sparseToDense.insert_or_assign<EntityId::Index_t>(lastEntityId, EntityId::Index_t{ id.index });
					}
				}

				static_for<0, sizeof...(TCmps)>([&](auto i) constexpr {
					auto& componentArray = std::get<i.value>(componentTuple);
					std::swap(componentArray[id.index], componentArray[entityAmount]);
					});
				std::swap(componentBitsets[id.index], componentBitsets[entityAmount]);
				++entityVersions[id.index];
			}

			static_for<0, sizeof...(TCmps)>([&](auto i) constexpr {
				std::get<i.value>(componentTuple).resize(entityAmount);
				});

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
				static constexpr int cmpIndex = get_index_in_pack<std::decay_t<T>, TCmps...>;
				static_assert(cmpIndex != -1, "Cannot find component T in typelist for Ecs");

				auto& cmpArray = std::get<cmpIndex>(componentTuple);
				cmpArray[arrayIndex] = std::forward<T>(cmp);
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
				static constexpr int cmpIndex = get_index_in_pack<std::decay_t<T>, TCmps...>;
				static_assert(cmpIndex != -1, "Cannot find component T in typelist for Ecs");

				auto& cmpArray = std::get<cmpIndex>(componentTuple);
				cmpArray[arrayIndex] = T{};
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
			static constexpr int cmpIndex = get_index_in_pack<T, TCmps...>;
			static_assert(cmpIndex != -1, "Cannot find component T in typelist for Ecs");

			auto [arrayIndex, valid] = GetIndexInArray(id);
			assert(valid);

			auto& cmpArray = std::get<cmpIndex>(componentTuple);
			return cmpArray[arrayIndex];
		}

		//TODO: Make a overload which takes a buffer instead of allocating all the time
		//! \Note: The vector of Entities will reserve a length of all entities. If memory is an issue, consider calling .shrink_to_fit()
		template<typename... Ts>
		[[nodiscard]] std::vector<EntityId> QueryEntities()
		{
			std::vector<EntityId> entities;
			//TODO: this is quite aggressive, but most performant. And .shrink_to_fit() can be called by the user later.
			entities.reserve(entityAmount);

			constexpr uint16_t componentMask = CreateBitsetFromTypes<Ts...>();
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
		static constexpr uint16_t CreateBitsetFromTypes()
		{
			uint16_t bits = 0;

			//TODO: Simplify by using folding expression over bitwise or
			(SetBitInBitsetFromType<Ts>(bits), ...);

			return bits;
		}

		template<typename T>
		static constexpr void SetBitInBitsetFromType(uint16_t& bits)
		{
			constexpr int index = get_index_in_pack<T, TCmps...>;
			static_assert(index != -1, "Cannot find type T in TCmps!");

			bits |= (1 << index);
		}
	};
}
