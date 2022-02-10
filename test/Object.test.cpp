#include <asx-object/Object.h>
#include <gtest/gtest.h>

using asx::object::Object;

namespace
{
	struct TypeOne : public Object
	{
	};

	struct TypeTwo : public Object
	{
	};

	struct TypeThree : public Object
	{
	};
}

TEST(Object, addChild)
{
	const auto parent = std::make_shared<Object>();
	const auto test = std::make_shared<Object>();
	EXPECT_TRUE(parent->addChild(test));
	EXPECT_FALSE(parent->addChild(test));
	EXPECT_TRUE(parent.get() == test->getParent());
}

TEST(Object, removeChild)
{
	const auto parent = std::make_shared<Object>();
	const auto test = std::make_shared<Object>();
	EXPECT_TRUE(parent->addChild(test));
	EXPECT_TRUE(parent->removeChild(test));
	EXPECT_FALSE(parent->removeChild(test));
	EXPECT_TRUE(test->getParent() == nullptr);
}

TEST(Object, getChild)
{
	const auto parent = std::make_shared<Object>();
	const auto test = std::make_shared<Object>();
	EXPECT_TRUE(parent->addChild(test));
	EXPECT_TRUE(test.get() == parent->getChild());
}

TEST(Object, getChildInvalid)
{
	const auto parent = std::make_shared<Object>();
	const auto test = std::make_shared<Object>();
	EXPECT_TRUE(parent->addChild(test));
	EXPECT_FALSE(test.get() == parent->getChild(1));
	EXPECT_TRUE(parent->getChild(1) == nullptr);
}

TEST(Object, getChildType)
{
	const auto parent = std::make_shared<Object>();
	const auto test = std::make_shared<Object>();
	EXPECT_TRUE(parent->addChild(test));
	EXPECT_TRUE(parent->addChild(std::make_shared<TypeOne>()));
	EXPECT_TRUE(parent->addChild(std::make_shared<TypeTwo>()));
	EXPECT_TRUE(parent->addChild(std::make_shared<TypeThree>()));
	EXPECT_EQ(parent->getChildren().size(), std::size_t{4});
	EXPECT_FALSE(parent->addChild(test));
	EXPECT_TRUE(parent.get() == test->getParent());

	EXPECT_TRUE(parent->getChild<TypeOne>() != nullptr);
	EXPECT_TRUE(parent->getChild<TypeTwo>() != nullptr);
	EXPECT_TRUE(parent->getChild<TypeThree>() != nullptr);
}
