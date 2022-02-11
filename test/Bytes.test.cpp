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

TEST(Bytes, array)
{
	constexpr auto test = std::array{std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), std::numeric_limits<int>::max(),
									 std::numeric_limits<int>::max()};
	auto value = asx::object::ToBytes(test);
	EXPECT_EQ(value.size(), sizeof(decltype(test)::size_type) + sizeof(decltype(test)::value_type) * test.size());

	const auto v = asx::object::BytesTo<std::array<int, 4>>(value);
	EXPECT_EQ(v, test);
}

TEST(Bytes, string)
{
	const auto test = std::string{std::numeric_limits<char>::max(), std::numeric_limits<char>::max(), std::numeric_limits<char>::max(),
								  std::numeric_limits<char>::max()};
	auto value = asx::object::ToBytes(test);
	EXPECT_EQ(value.size(), sizeof(decltype(test)::size_type) + sizeof(decltype(test)::value_type) * test.size());

	const auto v = asx::object::BytesTo<std::string>(value);
	EXPECT_EQ(v, test);
}

TEST(Bytes, array_string)
{
	const auto one = std::string{"one"};
	const auto two = std::string{"two"};
	const auto three = std::string{"three"};
	const auto four = std::string{"four"};
	const auto test = std::array{one, two, three, four};
	const auto byteSize = one.size() + two.size() + three.size() + four.size() + (sizeof(size_t) * 5);
	auto value = asx::object::ToBytes(test);
	EXPECT_EQ(value.size(), byteSize);

	const auto v = asx::object::BytesTo<std::array<std::string, 4>>(value);
	EXPECT_EQ(v, test);
}

TEST(Bytes, pair)
{
	const std::pair<int, int> test{std::numeric_limits<int>::min(), std::numeric_limits<int>::max()};
	auto value = asx::object::ToBytes(test);
	EXPECT_EQ(value.size(), sizeof(int) * 2);

	const auto v = asx::object::BytesTo<decltype(test)>(value);
	EXPECT_EQ(v, test);
}

TEST(Bytes, map)
{
	const std::map<int, int> test{{0, 0}, {1, 1}, {2, 2}};
	auto value = asx::object::ToBytes(test);
	EXPECT_EQ(value.size(), 32);

	const auto v = asx::object::BytesTo<decltype(test)>(value);
	EXPECT_EQ(v, test);
}

TEST(Bytes, unordered_map)
{
	const std::unordered_map<int, int> test{{0, 0}, {1, 1}, {2, 2}};
	auto value = asx::object::ToBytes(test);
	EXPECT_EQ(value.size(), 32);

	const auto v = asx::object::BytesTo<decltype(test)>(value);
	EXPECT_EQ(v, test);
}

TEST(Bytes, set)
{
	const std::set<int> test{std::numeric_limits<int>::max(), std::numeric_limits<int>::min()};
	auto value = asx::object::ToBytes(test);
	EXPECT_EQ(value.size(), sizeof(int) * 2 + sizeof(decltype(test)::size_type));

	const auto v = asx::object::BytesTo<decltype(test)>(value);
	EXPECT_EQ(v, test);
}

TEST(Bytes, unordered_set)
{
	const std::unordered_set<int> test{std::numeric_limits<int>::max(), std::numeric_limits<int>::min()};
	auto value = asx::object::ToBytes(test);
	EXPECT_EQ(value.size(), sizeof(int) * 2 + sizeof(decltype(test)::size_type));

	const auto v = asx::object::BytesTo<decltype(test)>(value);
	EXPECT_EQ(v, test);
}

TEST(Bytes, deque)
{
	const std::deque<int> test{std::numeric_limits<int>::max(), std::numeric_limits<int>::min()};
	auto value = asx::object::ToBytes(test);
	EXPECT_EQ(value.size(), sizeof(int) * 2 + sizeof(decltype(test)::size_type));

	const auto v = asx::object::BytesTo<decltype(test)>(value);
	EXPECT_EQ(v, test);
}

TEST(Bytes, vector)
{
	const std::vector<int> test{std::numeric_limits<int>::max(), std::numeric_limits<int>::min()};
	auto value = asx::object::ToBytes(test);
	EXPECT_EQ(value.size(), sizeof(int) * 2 + sizeof(decltype(test)::size_type));

	const auto v = asx::object::BytesTo<decltype(test)>(value);
	EXPECT_EQ(v, test);
}
