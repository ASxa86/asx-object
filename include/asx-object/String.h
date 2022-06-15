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
		using TNoRef = typename std::remove_const<typename std::remove_reference<T>::type>::type;

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

			using first_type = typename std::remove_const<typename std::remove_reference<typename TNoRef::first_type>::type>::type;

			if constexpr(asx::object::is_string<first_type>::value == true)
			{
				s += "\"";
			}

			s += ToString(x.first);

			if constexpr(asx::object::is_string<first_type>::value == true)
			{
				s += "\"";
			}

			s += ":";

			using second_type = typename std::remove_const<typename std::remove_reference<typename TNoRef::second_type>::type>::type;

			if constexpr(asx::object::is_string<second_type>::value == true)
			{
				s += "\"";
			}

			s += ToString(x.second);

			if constexpr(asx::object::is_string<second_type>::value == true)
			{
				s += "\"";
			}

			s += "}";
			return s;
		}
		else if constexpr(asx::object::is_container<TNoRef>::value == true || asx::object::is_array<TNoRef>::value == true)
		{
			std::string s = "[";

			for(const auto& i : x)
			{
				s += ToString(i);
				s += ", ";
			}

			if(std::size(s) > 1)
			{
				s.pop_back();
				s.pop_back();
			}

			s += "]";
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

			skipws();

			auto startIt = it;
			auto endIt = it;

			if(it != end && *it == '{')
			{
				++it;
				skipws();

				if(*it == '\"')
				{
					++it;
					startIt = it;

					while(it != end && *it != '\"')
					{
						++it;
					}

					endIt = it;
				}
				else
				{
					startIt = it;

					while(it != end && *it != ':')
					{
						++it;
					}

					endIt = it;
				}

				using first_type = typename std::remove_const<typename std::remove_reference<typename TNoRef::first_type>::type>::type;
				StringTo<first_type>(std::string_view{startIt, endIt}, t.first);

				while(it != end && *it != ':')
				{
					++it;
				}

				if(it != end && *it == ':')
				{
					++it;
					skipws();

					if(it != end && *it == '\"')
					{
						++it;
						startIt = it;

						while(it != end && *it != '\"')
						{
							++it;
						}

						endIt = it;
					}
					else
					{
						startIt = it;

						while(it != end && *it != '}')
						{
							++it;
						}

						endIt = it;
					}

					while(it != end && *it != '}')
					{
						++it;
					}

					using second_type = typename std::remove_const<typename std::remove_reference<typename TNoRef::second_type>::type>::type;
					StringTo<second_type>(std::string_view{startIt, endIt}, t.second);
				}
			}
		}
		else if constexpr(asx::object::is_container<TNoRef>::value == true)
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

			skipws();

			if(it != end && *it == '[')
			{
				while(it != end && *it != ']')
				{
					++it;

					skipws();

					startIt = it;

					while(it != end && *it != ',' && *it != ']')
					{
						++it;
					}

					endIt = it;

					using value_type = typename std::remove_const<typename std::remove_reference<typename TNoRef::value_type>::type>::type;

					if(startIt != endIt)
					{
						const auto value = StringTo<value_type>(std::string_view{startIt, endIt});
						t.insert(std::end(t), value);
					}
				}
			}
		}
		else if constexpr(asx::object::is_array<TNoRef>::value == true)
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

			skipws();

			auto arrayIt = std::begin(t);
			typename TNoRef::size_type i{};

			if(it != end && *it == '[')
			{
				while(it != end && *it != ']')
				{
					++it;

					skipws();

					startIt = it;

					while(it != end && *it != ',' && *it != ']')
					{
						++it;
					}

					endIt = it;

					using value_type = typename std::remove_const<typename std::remove_reference<typename TNoRef::value_type>::type>::type;

					const auto value = StringTo<value_type>(std::string_view{startIt, endIt});
					t[i] = value;
					i++;
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

		if constexpr(asx::object::is_pair<TNoRef>::value == true)
		{
			// Special case where key-value value_types for maps are const.
			using first_type = typename std::remove_const<typename TNoRef::first_type>::type;
			std::pair<first_type, typename TNoRef::second_type> t{};
			StringTo(x, t);
			return t;
		}
		else
		{
			TNoRef t{};
			StringTo(x, t);
			return t;
		}
	}
}