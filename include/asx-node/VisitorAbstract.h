#pragma once

namespace asx::node
{
	class NodeGroup;

	class VisitorAbstract
	{
	public:
		virtual ~VisitorAbstract() = default;
		virtual void accept(NodeGroup& x) = 0;
	};
}
