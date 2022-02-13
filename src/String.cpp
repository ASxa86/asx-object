#include <asx-object/String.h>

namespace
{
	// https://stackoverflow.com/questions/68472720/stdto-chars-minimal-floating-point-buffer-size
	template <typename T>
	constexpr int Log10ceil(T num)
	{
		return num < 10 ? 1 : 1 + Log10ceil(num / 10);
	}

	template <typename T>
	constexpr int BufferSizeScientific()
	{
		return 4 + std::numeric_limits<T>::max_digits10 + std::max(2, Log10ceil(std::numeric_limits<T>::max_exponent10));
	}

	template <typename T>
	constexpr int BufferSizeFixed()
	{
		return 2 + std::numeric_limits<T>::max_digits10 + std::numeric_limits<T>::max_exponent10;
	}
}

std::string asx::object::ToString(float x, int precision, std::chars_format fmt)
{
	std::string s;

	switch(fmt)
	{
		case std::chars_format::scientific:
			precision = std::min(precision, std::numeric_limits<float>::max_digits10 - 1);
			s.resize(BufferSizeScientific<float>());
			break;

		case std::chars_format::fixed:
			precision = std::min(precision, std::numeric_limits<float>::max_digits10 - 1);
			s.resize(BufferSizeFixed<float>());
			break;

		case std::chars_format::general:
			precision = std::min(precision, std::numeric_limits<float>::max_digits10);
			s.resize(BufferSizeScientific<float>());
			break;

		case std::chars_format::hex:
		default:
			break;
	}

	std::to_chars(s.data(), s.data() + s.size(), x, fmt, precision);

	return s;
}

std::string asx::object::ToString(double x, int precision, std::chars_format fmt)
{
	std::string s;

	switch(fmt)
	{
		case std::chars_format::scientific:
			precision = std::min(precision, std::numeric_limits<double>::max_digits10 - 1);
			s.resize(BufferSizeScientific<double>());
			break;

		case std::chars_format::fixed:
			precision = std::min(precision, std::numeric_limits<double>::max_digits10 - 1);
			s.resize(BufferSizeFixed<double>());
			break;

		case std::chars_format::general:
			precision = std::min(precision, std::numeric_limits<double>::max_digits10);
			s.resize(BufferSizeScientific<double>());
			break;

		case std::chars_format::hex:
		default:
			break;
	}

	std::to_chars(s.data(), s.data() + s.size(), x, fmt, precision);

	return s;
}
