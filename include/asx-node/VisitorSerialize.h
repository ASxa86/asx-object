#pragma once

#include <asx-node/VisitorAbstract.h>
#include <asx-node/export.hxx>

namespace asx::node
{
	class ASX_NODE_EXPORT VisitorSerialize : public VisitorAbstract
	{
	public:
		void accept(Node& x) override;
		void accept(NodeGroup& x) override;
	};
}
