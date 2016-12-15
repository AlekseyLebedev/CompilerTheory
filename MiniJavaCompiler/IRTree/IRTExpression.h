#pragma once

#include "IRTreeClasses.h"

namespace IRTree {

	class IRTExpression
    {
	public:
		
        virtual ~IRTExpression() {};
        virtual void Accept( IRTreeVisitor* visitor ) const = 0;

	};
}
