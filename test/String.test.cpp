#include <asx-object/String.h>
#include <gtest/gtest.h>

TEST(String, float)
{
	constexpr auto f = std::numeric_limits<float>::max();
	const auto string = asx::object::ToString(f);
	EXPECT_FLOAT_EQ(f, asx::object::StringTo<float>(string));
}

TEST(String, double)
{
	constexpr auto f = std::numeric_limits<double>::max();
	const auto string = asx::object::ToString(f);
	EXPECT_FLOAT_EQ(f, asx::object::StringTo<double>(string));
}

TEST(String, vector)
{
	constexpr std::string_view test{"[-1, 0, 1, 2]"};
}

TEST(String, pair_int)
{
	std::pair<int, int> test{std::numeric_limits<int>::max(), std::numeric_limits<int>::min()};
	const auto string = asx::object::ToString(test);
	const auto value = asx::object::StringTo<std::pair<int, int>>(string);
	EXPECT_EQ(value, test);
}

TEST(String, pair_string)
{
	std::pair<std::string, std::string> test{"hello world", "world, hello"};
	const auto string = asx::object::ToString(test);
	const auto value = asx::object::StringTo<std::pair<std::string, std::string>>(string);
	EXPECT_EQ(value, test);
}

TEST(String, map)
{
	constexpr std::string_view test{R"([{"k": -1}, {"k": 0}, {"k": 1}, {"k": 2}])"};
}
