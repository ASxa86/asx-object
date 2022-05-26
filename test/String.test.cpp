#include <asx-object/String.h>
#include <gtest/gtest.h>

TEST(String, bool)
{
	constexpr auto test{false};
	const auto string = asx::object::ToString(test);
	const auto value = asx::object::StringTo<bool>(string);
	EXPECT_EQ(value, test);
}

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

TEST(String, array)
{
	{
		std::array<std::string, 4> test{};
		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<decltype(test)>(string);
		EXPECT_EQ(value, test);
	}

	{
		std::array<std::string, 4> test{"a", "b", "c", "d"};
		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<decltype(test)>(string);
		EXPECT_EQ(value, test);
	}

	{
		std::array<int, 4> test{std::numeric_limits<int>::max(), 0, -std::numeric_limits<int>::max(), std::numeric_limits<int>::min()};
		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<decltype(test)>(string);
		EXPECT_EQ(value, test);
	}
}

TEST(String, vector)
{
	{
		std::vector<std::string> test{};
		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<decltype(test)>(string);
		EXPECT_EQ(value, test);
	}

	{
		std::vector<std::string> test{"a", "b", "c", "d"};
		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<decltype(test)>(string);
		EXPECT_EQ(value, test);
	}

	{
		std::vector<int> test{std::numeric_limits<int>::max(), 0, -std::numeric_limits<int>::max(), std::numeric_limits<int>::min()};
		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<decltype(test)>(string);
		EXPECT_EQ(value, test);
	}
}

TEST(String, deque)
{
	{
		std::deque<std::string> test{};
		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<decltype(test)>(string);
		EXPECT_EQ(value, test);
	}

	{
		std::deque<std::string> test{"a", "b", "c", "d"};
		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<decltype(test)>(string);
		EXPECT_EQ(value, test);
	}

	{
		std::deque<int> test{std::numeric_limits<int>::max(), 0, -std::numeric_limits<int>::max(), std::numeric_limits<int>::min()};
		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<decltype(test)>(string);
		EXPECT_EQ(value, test);
	}
}

TEST(String, set)
{
	{
		std::set<std::string> test{};
		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<decltype(test)>(string);
		EXPECT_EQ(value, test);
	}

	{
		std::set<std::string> test{"a", "b", "c", "d"};
		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<decltype(test)>(string);
		EXPECT_EQ(value, test);
	}

	{
		std::set<int> test{std::numeric_limits<int>::max(), 0, -std::numeric_limits<int>::max(), std::numeric_limits<int>::min()};
		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<decltype(test)>(string);
		EXPECT_EQ(value, test);
	}
}

TEST(String, unordered_set)
{
	{
		std::unordered_set<std::string> test{};
		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<decltype(test)>(string);
		EXPECT_EQ(value, test);
	}

	{
		std::unordered_set<std::string> test{"a", "b", "c", "d"};
		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<decltype(test)>(string);
		EXPECT_EQ(value, test);
	}

	{
		std::unordered_set<int> test{std::numeric_limits<int>::max(), 0, -std::numeric_limits<int>::max(), std::numeric_limits<int>::min()};
		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<decltype(test)>(string);
		EXPECT_EQ(value, test);
	}
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
	{
		std::pair<std::string, std::string> test{};
		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<decltype(test)>(string);
		EXPECT_EQ(value, test);
	}

	{
		std::pair<std::string, std::string> test{"hello world", "world, hello"};
		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<std::pair<std::string, std::string>>(string);
		EXPECT_EQ(value, test);
	}

	{
		std::pair<std::string, std::string> test{"{hello world}:", "{world, hello}"};
		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<std::pair<std::string, std::string>>(string);
		EXPECT_EQ(value, test);
	}
}

TEST(String, pair_int_string)
{
	{
		std::pair<std::string, int> test{};
		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<decltype(test)>(string);
		EXPECT_EQ(value, test);
	}

	{
		std::pair<std::string, int> test{"hello world", std::numeric_limits<int>::max()};
		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<std::pair<std::string, int>>(string);
		EXPECT_EQ(value, test);
	}

	{
		std::pair<int, std::string> test{std::numeric_limits<int>::max(), "hello world"};
		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<std::pair<int, std::string>>(string);
		EXPECT_EQ(value, test);
	}
}

TEST(String, map)
{
	{
		std::map<std::string, int> test{};
		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<decltype(test)>(string);
		EXPECT_EQ(value, test);
	}

	{
		std::map<std::string, int> test{
			{"a", std::numeric_limits<int>::max()}, {"b", 0}, {"c", -std::numeric_limits<int>::max()}, {"d", std::numeric_limits<int>::min()}};
		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<decltype(test)>(string);
		EXPECT_EQ(value, test);
	}

	{
		std::map<int, std::string> test{
			{std::numeric_limits<int>::max(), "a"}, {0, "b"}, {-std::numeric_limits<int>::max(), "c"}, {std::numeric_limits<int>::min(), "d"}};
		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<decltype(test)>(string);
		EXPECT_EQ(value, test);
	}
}

TEST(String, unordered_map)
{
	{
		std::unordered_map<std::string, int> test{};
		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<decltype(test)>(string);
		EXPECT_EQ(value, test);
	}

	{
		std::unordered_map<std::string, int> test{
			{"a", std::numeric_limits<int>::max()}, {"b", 0}, {"c", -std::numeric_limits<int>::max()}, {"d", std::numeric_limits<int>::min()}};
		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<decltype(test)>(string);
		EXPECT_EQ(value, test);
	}

	{
		std::unordered_map<int, std::string> test{
			{std::numeric_limits<int>::max(), "a"}, {0, "b"}, {-std::numeric_limits<int>::max(), "c"}, {std::numeric_limits<int>::min(), "d"}};
		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<decltype(test)>(string);
		EXPECT_EQ(value, test);
	}
}

TEST(String, voltron)
{
	{
		std::unordered_map<std::string, std::vector<std::pair<float, bool>>> test{{{}, {}}};
		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<decltype(test)>(string);
		EXPECT_EQ(value, test);
	}

	{
		std::unordered_map<std::string, std::vector<std::pair<int, bool>>> test{
			{"a", {{1, true}, {2, false}}},
			{"b", {{-1, false}, {3, true}}},
			{"c", {{-1, true}, {4, false}}},
			{"d", {{1, false}, {5, true}}},
		};

		const auto string = asx::object::ToString(test);
		const auto value = asx::object::StringTo<decltype(test)>(string);
		EXPECT_EQ(value, test);
	}
}
