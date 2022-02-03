#include <asx-node/Node.h>
#include <gtest/gtest.h>

TEST(Node, setName)
{
	asx::node::Node node;

	constexpr std::string_view name{"name"};
	node.setName(name);
	EXPECT_EQ(name, node.getName());
}
