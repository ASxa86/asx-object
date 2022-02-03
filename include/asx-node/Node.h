#pragma once

#include <asx-node/NodeAbstract.h>
#include <asx-node/export.hxx>
#include <string_view>

namespace asx::node
{
	class NodeGroup;

	class ASX_NODE_EXPORT Node : public NodeAbstract
	{
	public:
		Node() = default;
		virtual ~Node() = default;

		Node(const Node&) = delete;
		Node& operator=(const Node&) = delete;

		void accept(VisitorAbstract& x) override;

		void setName(std::string_view x);
		std::string_view getName() const noexcept;

		void setParent(NodeGroup* x) noexcept;
		NodeGroup* getParent() const noexcept;

	private:
		std::string name;
		NodeGroup* parent{nullptr};
	};
}
