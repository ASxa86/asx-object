#include <asx-node/Node.h>
#include <asx-node/NodeGroup.h>

using asx::node::Node;

void Node::accept(VisitorAbstract& x)
{
	x.accept(*this);
}

void Node::setName(std::string_view x)
{
	this->name = x;
}

std::string_view Node::getName() const noexcept
{
	return this->name;
}

void Node::setParent(asx::node::NodeGroup* x) noexcept
{
	this->parent = x;
}

asx::node::NodeGroup* Node::getParent() const noexcept
{
	return this->parent;
}
