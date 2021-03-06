#pragma once
#include <type_traits>
#include <cstdint>
#include <utility>

#include "engine/Defines.h"


namespace eyos {
	template<typename... Ts>
	struct Types{};
	
	template<typename T, int N, typename... Ts>
	struct get_index_in_pack_impl;

	template<typename T, int N, typename T0, typename... Ts>
	struct get_index_in_pack_impl<T, N, T0, Ts...>
	{
		static constexpr int value =
			std::is_same_v<T, T0> ?
			N :
			get_index_in_pack_impl<T, (N + 1), Ts...>::value;
	};

	template<typename T, int N, typename T0>
	struct get_index_in_pack_impl<T, N, T0>
	{
		static constexpr int value = std::is_same_v<T, T0> ? N : -1;
	};

	template<typename T, int N>
	struct get_index_in_pack_impl<T, N>
	{
		static constexpr int value = -1;
	};

	template<typename T, typename... Ts>
	constexpr int get_index_in_pack = get_index_in_pack_impl<T, 0, Ts...>::value;


	template <int First, int Last, typename Lambda>
	inline void static_for(Lambda const& f)
	{
		if constexpr (First < Last)
		{
			f(std::integral_constant<int, First>{});
			static_for<First + 1, Last>(f);
		}
		else {
			(void)f;
		}
	}

	template<typename T>
	struct MakeRefARefWrapper
	{
		using type = T;
	};
	template<typename T>
	struct MakeRefARefWrapper<T&>
	{
		using type = std::reference_wrapper<T>;
	};
	
	//! When T is a & type, a std::reference_wrapper<T> is returned, otherwise just T is returned
	//! This is used internally to store reference types in a query
	template<typename T>
	using MakeRefARefWrapper_t = typename MakeRefARefWrapper<T>::type;

	template<typename T>
	MakeRefARefWrapper_t<T> make_ref_a_ref_wrapper(T&& t)
	{
		return MakeRefARefWrapper_t<T>{t};
	}

	using TemplateTypeId = uint32_t;
	
	constexpr TemplateTypeId g_invalidTemplateTypeId = 0;

	EYOS_API extern TemplateTypeId typeIdCounter;

	template<typename T>
	TemplateTypeId GetTemplateTypeId()
	{
		static TemplateTypeId templateTypeId = ++typeIdCounter;

		return templateTypeId;
	}

	template<typename T>
	void DeconstructThing(void* ptr) {
		reinterpret_cast<T*>(ptr)->~T();
	}

	template<typename T>
	void ConstructThing(void* ptr) {
		new (ptr) T();
	}

	template<typename T>
	void MoveThing(void* to, void* from) {
		*reinterpret_cast<T*>(to) = std::move(*reinterpret_cast<T*>(from));
	}

	template<typename T1, typename T2>
	void SwapThings(void* a, void* b)
	{
		std::swap(*reinterpret_cast<T1*>(a), *reinterpret_cast<T2*>(b));
	}
}
