#include <asx-object/TypeTraits.h>
#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <list>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

TEST(TypeTraits, pod)
{
	auto test = asx::object::is_container<char>::value;
	EXPECT_FALSE(test);

	test = asx::object::is_container<int>::value;
	EXPECT_FALSE(test);

	test = asx::object::is_container<double>::value;
	EXPECT_FALSE(test);
}

TEST(TypeTraits, map)
{
	auto test = asx::object::is_container<std::map<int, int>>::value;
	EXPECT_TRUE(test);

	test = asx::object::is_container<std::map<std::string, int>>::value;
	EXPECT_TRUE(test);

	test = asx::object::is_container<std::map<std::string, std::string>>::value;
	EXPECT_TRUE(test);

	test = asx::object::is_map<std::map<std::string, std::string>>::value;
	EXPECT_TRUE(test);
}

TEST(TypeTraits, vector)
{
	auto test = asx::object::is_container<std::vector<int>>::value;
	EXPECT_TRUE(test);

	test = asx::object::is_container<std::vector<std::string>>::value;
	EXPECT_TRUE(test);
}

TEST(TypeTraits, array)
{
	auto test = asx::object::is_container<std::array<int, sizeof(int)>>::value;
	EXPECT_TRUE(test);

	test = asx::object::is_container<std::array<std::string, sizeof(std::string)>>::value;
	EXPECT_TRUE(test);
}
