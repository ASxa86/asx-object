#pragma once

#include <asx-object/TypeTraits.h>
#include <asx-object/export.hxx>
#include <cstddef>
#include <span>
#include <vector>

namespace asx::object
{
	template <typename T>
	auto ToBytes([[maybe_unused]] const T& x)
	{
		using TNoRef = typename std::remove_reference<T>::type;

		std::vector<std::byte> v;

		if constexpr(std::is_arithmetic_v<TNoRef> == true)
		{
			v.resize(sizeof(TNoRef));
			std::memcpy(v.data(), &x, sizeof(x));
		}
		else if constexpr(asx::object::is_array<TNoRef>::value == true || std::is_same<TNoRef, std::string>::value == true
						  || std::is_same<TNoRef, std::string_view>::value == true || asx::object::is_set<TNoRef>::value == true
						  || asx::object::is_unordered_set<TNoRef>::value == true || asx::object::is_deque<TNoRef>::value == true
						  || asx::object::is_vector<TNoRef>::value == true)
		{
			auto b = ToBytes(x.size());
			v.insert(std::end(v), std::cbegin(b), std::cend(b));

			for(const auto& i : x)
			{
				b = ToBytes(i);
				v.insert(std::end(v), std::cbegin(b), std::cend(b));
			}
		}
		else if constexpr(asx::object::is_pair<TNoRef>::value == true)
		{
			auto b = ToBytes(x.first);
			v.insert(std::end(v), std::cbegin(b), std::cend(b));

			b = ToBytes(x.second);
			v.insert(std::end(v), std::cbegin(b), std::cend(b));
		}
		else if constexpr(asx::object::is_map<TNoRef>::value == true || asx::object::is_unordered_map<TNoRef>::value == true)
		{
			auto b = ToBytes(x.size());
			v.insert(std::end(v), std::cbegin(b), std::cend(b));

			for(const auto& pair : x)
			{
				auto p = ToBytes(pair);
				v.insert(std::end(v), std::begin(p), std::end(p));
			}
		}

		return v;
	}

	template <typename T>
	auto BytesTo(std::span<std::byte> x);

	template <typename T>
	std::size_t BytesTo([[maybe_unused]] std::span<std::byte> x, T& t)
	{
		using TNoRef = typename std::remove_reference<T>::type;

		if constexpr(std::is_arithmetic_v<TNoRef> == true)
		{
			std::memcpy(&t, x.data(), sizeof(t));
			return sizeof(t);
		}
		else if constexpr(asx::object::is_array<TNoRef>::value == true)
		{
			auto skip = sizeof(TNoRef::size_type);

			for(auto& i : t)
			{
				skip += BytesTo<typename TNoRef::value_type>(std::span{std::cbegin(x) + skip, std::cend(x)}, i);
			}

			return skip;
		}
		else if constexpr(std::is_same<TNoRef, std::string>::value == true || std::is_same<TNoRef, std::string_view>::value == true
						  || asx::object::is_vector<TNoRef>::value == true || asx::object::is_deque<TNoRef>::value == true)
		{
			typename TNoRef::size_type s{};

			auto skip = BytesTo<decltype(s)>(x, s);

			t.resize(s);

			for(auto& i : t)
			{
				skip += BytesTo<decltype(i)>(std::span{std::cbegin(x) + skip, std::cend(x)}, i);
			}

			return skip;
		}
		else if constexpr(asx::object::is_pair<TNoRef>::value == true)
		{
			typename TNoRef::first_type f{};
			auto skip = BytesTo<decltype(f)>(x, f);

			typename TNoRef::second_type s{};
			skip += BytesTo<decltype(s)>(std::span{std::cbegin(x) + skip, std::cend(x)}, s);

			t = {f, s};

			return skip;
		}
		else if constexpr(asx::object::is_map<TNoRef>::value == true || asx::object::is_unordered_map<TNoRef>::value == true)
		{
			typename TNoRef::size_type s{};

			auto skip = BytesTo<decltype(s)>(x, s);

			for(decltype(s) i{}; i < s; i++)
			{
				std::pair<typename TNoRef::key_type, typename TNoRef::mapped_type> p;
				skip += BytesTo<decltype(p)>(std::span{std::cbegin(x) + skip, std::cend(x)}, p);

				t.emplace(p);
			}

			return skip;
		}
		else if constexpr(asx::object::is_set<TNoRef>::value == true || asx::object::is_unordered_set<TNoRef>::value == true)
		{
			typename TNoRef::size_type s{};
			auto skip = BytesTo<decltype(s)>(x, s);

			for(decltype(s) i{}; i < s; i++)
			{
				typename TNoRef::key_type k{};
				skip += BytesTo<decltype(k)>(std::span{std::cbegin(x) + skip, std::cend(x)}, k);
				t.insert(k);
			}

			return skip;
		}
	}

	template <typename T>
	auto BytesTo(std::span<std::byte> x)
	{
		using TNoRef = typename std::remove_const<typename std::remove_reference<T>::type>::type;

		TNoRef t{};
		asx::object::BytesTo(x, t);
		return t;
	}
}
