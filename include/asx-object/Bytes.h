#pragma once

#include <asx-object/TypeTraits.h>
#include <asx-object/export.hxx>
#include <cstddef>
#include <span>
#include <vector>

namespace asx::object
{
	template <typename T>
	std::vector<std::byte> ToBytes([[maybe_unused]] const T& x)
	{
		using TNoRef = typename std::remove_reference<T>::type;

		std::vector<std::byte> v;

		if constexpr(std::is_arithmetic_v<TNoRef> == true)
		{
			v.resize(sizeof(TNoRef));
			std::memcpy(v.data(), &x, sizeof(x));
		}
		else if constexpr(asx::object::is_array<TNoRef>::value == true || std::is_same<TNoRef, std::string>::value == true
						  || std::is_same<TNoRef, std::string_view>::value == true)
		{
			auto b = ToBytes(x.size());
			v.insert(std::end(v), std::begin(b), std::end(b));

			for(const auto& i : x)
			{
				b = ToBytes(i);
				v.insert(std::end(v), std::begin(b), std::end(b));
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
				skip += BytesTo<TNoRef::value_type>(std::span{std::begin(x) + skip, std::end(x)}, i);
			}

			return x.size();
		}
		else if constexpr(std::is_same<TNoRef, std::string>::value == true || std::is_same<TNoRef, std::string_view>::value == true)
		{
			typename TNoRef::size_type s{};

			auto skip = BytesTo<TNoRef::size_type>(x, s);

			t.resize(s);

			for(auto& i : t)
			{
				skip += BytesTo<decltype(i)>(std::span{std::begin(x) + skip, std::end(x)}, i);
			}

			return t.size() * sizeof(TNoRef::value_type);
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
