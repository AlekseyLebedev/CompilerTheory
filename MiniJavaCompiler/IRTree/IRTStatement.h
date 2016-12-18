#pragma once

#include "INode.h"
#include "IRTreeClasses.h"

namespace IRTree {

	class IRTStatement : public INode
    {
	public:
		
		virtual ~IRTStatement() {};
		virtual void Accept( IRTreeVisitor* visitor ) const = 0;

	};
}
