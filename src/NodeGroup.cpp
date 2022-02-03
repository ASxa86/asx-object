#include <asx-node/NodeGroup.h>
#include <algorithm>

using asx::node::NodeGroup;

bool NodeGroup::addChild(std::unique_ptr<asx::node::Node> x)
{
	x->setParent(this);
	this->children.emplace_back(std::move(x));
	return true;
}

bool NodeGroup::removeChild(asx::node::Node* x)
{
	const auto ret = std::ranges::remove_if(this->children, [x](auto&& n) { return n.get() == x; });
	x->setParent(nullptr);
	this->children.erase(std::begin(ret), std::end(ret));
	return true;
}

asx::node::Node* NodeGroup::getChild(std::vector<std::unique_ptr<asx::node::Node>>::size_type x) const
{
	return this->children[x].get();
}

const std::vector<std::unique_ptr<asx::node::Node>>& NodeGroup::getChildren() const
{
	return this->children;
}
