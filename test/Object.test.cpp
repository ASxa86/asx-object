#include <asx-object/Object.h>
#include <gtest/gtest.h>

using asx::object::Object;

TEST(Object, addChild)
{
	const auto parent = std::make_shared<Object>();
	const auto test = std::make_shared<Object>();
	EXPECT_TRUE(parent->addChild(test));
	EXPECT_FALSE(parent->addChild(test));
}

TEST(Object, removeChild)
{
	const auto parent = std::make_shared<Object>();
	const auto test = std::make_shared<Object>();
	EXPECT_TRUE(parent->addChild(test));
	EXPECT_TRUE(parent->removeChild(test));
	EXPECT_FALSE(parent->removeChild(test));
}