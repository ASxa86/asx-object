#pragma once

#include <array>
#include <chrono>
#include <deque>
#include <map>
#include <set>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

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
	struct is_pair : std::false_type
	{
	};

	template <typename K, typename V>
	struct is_pair<std::pair<K, V>> : std::true_type
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

	template <typename T>
	struct is_set : std::false_type
	{
	};

	template <typename T>
	struct is_set<std::set<T>> : std::true_type
	{
	};

	template <typename T>
	struct is_unordered_set : std::false_type
	{
	};

	template <typename T>
	struct is_unordered_set<std::unordered_set<T>> : std::true_type
	{
	};

	template <typename T>
	struct is_vector : std::false_type
	{
	};

	template <typename T>
	struct is_vector<std::vector<T>> : std::true_type
	{
	};

	template <typename T>
	struct is_deque : std::false_type
	{
	};

	template <typename T>
	struct is_deque<std::deque<T>> : std::true_type
	{
	};

	template <class T>
	struct is_duration : std::false_type
	{
	};

	template <class Rep, class Period>
	struct is_duration<std::chrono::duration<Rep, Period>> : std::true_type
	{
	};
}
