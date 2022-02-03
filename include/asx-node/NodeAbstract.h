#pragma once

#include <asx-node/VisitorAbstract.h>

namespace asx::node
{
	class NodeAbstract
	{
	public:
		virtual ~NodeAbstract() = default;
		virtual void accept(VisitorAbstract& x) = 0;
	};
}
