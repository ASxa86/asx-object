#include <asx-object/Bytes.h>
#include <gtest/gtest.h>

TEST(Bytes, char_ToBytes)
{
	constexpr auto test{std::numeric_limits<char>::max()};
	const auto value = asx::object::ToBytes(test);
	EXPECT_EQ(value.size(), sizeof(test));
}

TEST(Bytes, char_BytesTo)
{
	constexpr auto test{std::numeric_limits<char>::max()};
	std::vector<std::byte> value{sizeof(test)};
	std::memcpy(value.data(), &test, sizeof(test));

	EXPECT_EQ(asx::object::BytesTo<char>(value), test);
}

TEST(Bytes, short_ToBytes)
{
	constexpr auto test{std::numeric_limits<short>::max()};
	const auto value = asx::object::ToBytes(test);
	EXPECT_EQ(value.size(), sizeof(test));
}

TEST(Bytes, short_BytesTo)
{
	constexpr auto test{std::numeric_limits<short>::max()};
	std::vector<std::byte> value{sizeof(test)};
	std::memcpy(value.data(), &test, sizeof(test));

	EXPECT_EQ(asx::object::BytesTo<short>(value), test);
}

TEST(Bytes, int_ToBytes)
{
	constexpr auto test{std::numeric_limits<int>::max()};
	const auto value = asx::object::ToBytes(test);
	EXPECT_EQ(value.size(), sizeof(test));
}

TEST(Bytes, int_BytesTo)
{
	constexpr auto test{std::numeric_limits<int>::max()};
	std::vector<std::byte> value{sizeof(test)};
	std::memcpy(value.data(), &test, sizeof(test));

	EXPECT_EQ(asx::object::BytesTo<int>(value), test);
}

TEST(Bytes, long_ToBytes)
{
	constexpr auto test{std::numeric_limits<long>::max()};
	const auto value = asx::object::ToBytes(test);
	EXPECT_EQ(value.size(), sizeof(test));
}

TEST(Bytes, long_BytesTo)
{
	constexpr auto test{std::numeric_limits<long>::max()};
	std::vector<std::byte> value{sizeof(test)};
	std::memcpy(value.data(), &test, sizeof(test));

	EXPECT_EQ(asx::object::BytesTo<long>(value), test);
}

TEST(Bytes, longlong_ToBytes)
{
	constexpr auto test{std::numeric_limits<long long>::max()};
	const auto value = asx::object::ToBytes(test);
	EXPECT_EQ(value.size(), sizeof(test));
}

TEST(Bytes, longlong_BytesTo)
{
	constexpr auto test{std::numeric_limits<long long>::max()};
	std::vector<std::byte> value{sizeof(test)};
	std::memcpy(value.data(), &test, sizeof(test));

	EXPECT_EQ(asx::object::BytesTo<long long>(value), test);
}

TEST(Bytes, float_ToBytes)
{
	constexpr auto test{std::numeric_limits<float>::max()};
	const auto value = asx::object::ToBytes(test);
	EXPECT_EQ(value.size(), sizeof(test));
}

TEST(Bytes, float_BytesTo)
{
	constexpr auto test{std::numeric_limits<float>::max()};
	std::vector<std::byte> value{sizeof(test)};
	std::memcpy(value.data(), &test, sizeof(test));

	EXPECT_EQ(asx::object::BytesTo<float>(value), test);
}

TEST(Bytes, double_ToBytes)
{
	constexpr auto test{std::numeric_limits<double>::max()};
	const auto value = asx::object::ToBytes(test);
	EXPECT_EQ(value.size(), sizeof(test));
}

TEST(Bytes, double_BytesTo)
{
	constexpr auto test{std::numeric_limits<double>::max()};
	std::vector<std::byte> value{sizeof(test)};
	std::memcpy(value.data(), &test, sizeof(test));

	EXPECT_EQ(asx::object::BytesTo<double>(value), test);
}
