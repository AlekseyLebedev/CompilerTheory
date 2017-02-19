#pragma once

#include "INode.h"

namespace IRTree {

	class IRTExpression : public INode
    {
	public:
		
        virtual ~IRTExpression() {};
        virtual void Accept( IVisitor* visitor ) const = 0;

	};
}
