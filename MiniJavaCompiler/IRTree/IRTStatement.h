#pragma once

#include "INode.h"

namespace IRTree {

	class IRTStatement : public INode
    {
	public:
		
		virtual ~IRTStatement() {};
		virtual void Accept( IVisitor* visitor ) const = 0;

	};
}
