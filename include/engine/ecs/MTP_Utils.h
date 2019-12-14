#pragma once
#include <type_traits>


namespace eyos {
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
}
