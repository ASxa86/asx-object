#pragma once

#include <asx-object/TypeTraits.h>
#include <array>
#include <asx-object/export.hxx>
#include <charconv>
#include <filesystem>
#include <sstream>
#include <string>
#include <vector>

namespace asx::object
{
	///
	///	\brief Special ToString overload to support floating point precision and format.
	///
	///	\param x The float to convert.
	///	\param precision The decimal precision to output.
	///	\param fmt Specify either scientific or fixed format.
	///
	ASX_OBJECT_EXPORT std::string ToString(float x, int precision = std::numeric_limits<float>::max_digits10,
										   std::chars_format fmt = std::chars_format::fixed);

	///
	///	\brief Special ToString overload to support floating point precision and format.
	///
	///	\param x The double to convert.
	///	\param precision The decimal precision to output.
	///	\param fmt Specify either scientific or fixed format.
	///
	ASX_OBJECT_EXPORT std::string ToString(double x, int precision = std::numeric_limits<double>::max_digits10,
										   std::chars_format fmt = std::chars_format::fixed);

	///
	///	\brief Generic type conversion/serialization to a std::string.
	///
	///	Complex types such as containers and classes will be serialized as json strings.
	///
	template <typename T>
	std::string ToString([[maybe_unused]] const T& x)
	{
		using TNoRef = typename std::remove_reference<T>::type;

		if constexpr(asx::object::is_duration<TNoRef>::value == true)
		{
			return ToString(x.count());
		}
		else if constexpr(std::is_same<bool, TNoRef>::value == true)
		{
			return x ? "true" : "false";
		}
		else if constexpr(std::is_same<std::filesystem::path, TNoRef>::value == true)
		{
			return x.string();
		}
		else if constexpr(std::is_arithmetic<TNoRef>::value == true)
		{
			std::array<char, 100> buffer{};
			const auto [p, ec] = std::to_chars(buffer.data(), buffer.data() + buffer.size(), x);

			if(ec == std::errc())
			{
				return std::string(buffer.data(), p - buffer.data());
			}

			return {};
		}
		else if constexpr(std::is_enum<TNoRef>::value == true)
		{
			// Parse enumas as strings.
		}
		else if constexpr(std::is_convertible<TNoRef, std::string>::value == true)
		{
			return static_cast<std::string>(x);
		}
		else if constexpr(std::is_same<std::string, TNoRef>::value == true)
		{
			return x;
		}
		else if constexpr(asx::object::is_pair<TNoRef>::value == true)
		{
			std::string s = "{";

			if constexpr(std::is_same<std::string, TNoRef::first_type>::value == true)
			{
				s += "\"";
			}

			s += ToString(x.first);

			if constexpr(std::is_same<std::string, TNoRef::first_type>::value == true)
			{
				s += "\"";
			}

			s += ":";

			if constexpr(std::is_same<std::string, TNoRef::first_type>::value == true)
			{
				s += "\"";
			}

			s += ToString(x.second);

			if constexpr(std::is_same<std::string, TNoRef::first_type>::value == true)
			{
				s += "\"";
			}

			s += "}";
			return s;
		}
		else if constexpr(std::is_class<TNoRef>::value == true)
		{
			// Parse stl containers into json like format [].
		}
	}

	template <typename T>
	typename std::remove_reference<T>::type StringTo(std::string_view x);

	template <typename T>
	void StringTo([[maybe_unused]] std::string_view x, T& t)
	{
		using TNoRef = typename std::remove_reference<T>::type;

		if constexpr(asx::object::is_duration<TNoRef>::value == true)
		{
			t = TNoRef{StringTo<typename TNoRef::rep>(x)};
		}
		else if constexpr(std::is_same<bool, TNoRef>::value == true)
		{
			t = (x == "true") ? true : false;
		}
		else if constexpr(std::is_same<std::filesystem::path, TNoRef>::value == true)
		{
			t = x;
		}
		else if constexpr(std::is_arithmetic<TNoRef>::value == true)
		{
			std::from_chars(x.data(), x.data() + x.size(), t);
		}
		else if constexpr(std::is_enum<TNoRef>::value == true)
		{
			// Parse enums as strings.
		}
		else if constexpr(std::is_same<std::string, TNoRef>::value == true)
		{
			t = x;
		}
		else if constexpr(asx::object::is_pair<TNoRef>::value == true)
		{
			auto it = std::begin(x);
			const auto end = std::end(x);

			const auto skipws = [&it, end]
			{
				while(it != end && (*it == ' ' || *it == '\t'))
				{
					++it;
				}
			};

			auto startIt = it;
			auto endIt = it;

			if(it != std::end(x) && *it == '{')
			{
				++it;
				skipws();

				if(*it == '\"')
				{
					++it;
					startIt = it;

					while(it != std::end(x) && *it != '\"')
					{
						++it;
					}

					endIt = it;
				}
				else
				{
					startIt = it;

					while(it != std::end(x) && *it != ':')
					{
						++it;
					}

					endIt = it;
				}

				StringTo<TNoRef::first_type>(std::string_view{startIt, endIt}, t.first);

				while(it != std::end(x) && *it != ':')
				{
					++it;
				}

				if(it != std::end(x) && *it == ':')
				{
					++it;
					skipws();

					if(it != std::end(x) && *it == '\"')
					{
						++it;
						startIt = it;

						while(it != std::end(x) && *it != '\"')
						{
							++it;
						}

						endIt = it;
					}
					else
					{
						startIt = it;

						while(it != std::end(x) && *it != '}')
						{
							++it;
						}

						endIt = it;
					}

					while(it != std::end(x) && *it != '}')
					{
						++it;
					}

					StringTo<TNoRef::first_type>(std::string_view{startIt, endIt}, t.second);
				}
			}
		}
		else if constexpr(std::is_class<TNoRef>::value == true)
		{
			// Parse stl containers into json like format [].
		}
	}

	template <typename T>
	typename std::remove_reference<T>::type StringTo(std::string_view x)
	{
		using TNoRef = typename std::remove_const<typename std::remove_reference<T>::type>::type;

		TNoRef t{};
		StringTo(x, t);
		return t;
	}
}