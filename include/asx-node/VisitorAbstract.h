#pragma once

namespace asx::node
{
	class Node;
	class NodeGroup;

	class VisitorAbstract
	{
	public:
		virtual ~VisitorAbstract() = default;
		virtual void accept(Node& x) = 0;
		virtual void accept(NodeGroup& x) = 0;
	};
}
