#include <asx-node/NodeGroup.h>
#include <gtest/gtest.h>

TEST(NodeGroup, addChild)
{
	auto node = std::make_unique<asx::node::Node>();
	auto group = std::make_unique<asx::node::NodeGroup>();
	group->addChild(std::move(node));

	EXPECT_TRUE(node.get() == group->getChild());
}
