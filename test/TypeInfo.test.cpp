#include <asx-object/TypeInfo.h>
#include <gtest/gtest.h>

namespace asx::object
{
	class TypeOne
	{
	};

	struct TypeTwo
	{
	};
}

TEST(TypeInfo, typeName_struct)
{
	constexpr std::string_view test = asx::object::GetTypeName<asx::object::TypeTwo>();
	EXPECT_EQ(test, "asx::object::TypeTwo");
}

TEST(TypeInfo, typeName_class)
{
	constexpr std::string_view test = asx::object::GetTypeName<asx::object::TypeOne>();
	EXPECT_EQ(test, "asx::object::TypeOne");
}
