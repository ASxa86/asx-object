#pragma once

#include <asx-node/Node.h>
#include <memory>
#include <vector>

namespace asx::node
{
	class ASX_NODE_EXPORT NodeGroup : public Node
	{
	public:
		bool addChild(std::unique_ptr<Node> x);
		bool removeChild(Node* x);
		Node* getChild(std::vector<std::unique_ptr<Node>>::size_type x = 0) const;

		const std::vector<std::unique_ptr<Node>>& getChildren() const;

	private:
		std::vector<std::unique_ptr<Node>> children;
	};
}