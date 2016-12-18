#pragma once

#include "INode.h"
#include "IRTreeClasses.h"

namespace IRTree {

	class IRTExpression : public INode
    {
	public:
		
        virtual ~IRTExpression() {};
        virtual void Accept( IRTreeVisitor* visitor ) const = 0;

	};
}
