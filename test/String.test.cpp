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
