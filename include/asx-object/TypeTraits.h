#pragma once

#include <array>
#include <map>
#include <type_traits>
#include <unordered_map>

namespace asx::object
{
	template <typename T, typename _ = void>
	struct is_container : std::false_type
	{
	};

	template <typename T>
	struct is_container<
		T,
		std::conditional_t<false,
						   std::void_t<typename T::value_type, typename T::size_type, typename T::allocator_type, typename T::iterator,
									   typename T::const_iterator, decltype(std::declval<T>().size()), decltype(std::declval<T>().begin()),
									   decltype(std::declval<T>().end()), decltype(std::declval<T>().cbegin()), decltype(std::declval<T>().cend())>,
						   void>> : public std::true_type
	{
	};

	template <typename T>
	struct is_array : std::false_type
	{
	};

	template <typename T, std::size_t S>
	struct is_array<std::array<T, S>> : std::true_type
	{
	};

	template <typename T>
	struct is_map : std::false_type
	{
	};

	template <typename K, typename V>
	struct is_map<std::map<K, V>> : std::true_type
	{
	};

	template <typename T>
	struct is_unordered_map : std::false_type
	{
	};

	template <typename K, typename V>
	struct is_unordered_map<std::unordered_map<K, V>> : std::true_type
	{
	};
}
