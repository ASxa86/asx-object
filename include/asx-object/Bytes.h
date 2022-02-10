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
		else if constexpr(asx::object::is_array<TNoRef> == true)
		{
		}

		return v;
	}

	template <typename T>
	auto BytesTo(std::span<std::byte> x);

	template <typename T>
	void BytesTo([[maybe_unused]] std::span<std::byte> x, T& t)
	{
		using TNoRef = typename std::remove_reference<T>::type;

		if constexpr(std::is_arithmetic_v<TNoRef> == true)
		{
			std::memcpy(&t, x.data(), x.size());
		}
		else if constexpr(asx::object::is_array<TNoRef> == true)
		{
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
