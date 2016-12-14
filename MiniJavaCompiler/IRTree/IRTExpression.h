#pragma once

#include "IRTree.h"

namespace IRTree {

	class IRTExpression {
	public:
		
        virtual ~IRTExpression() {};
        virtual void Accept( IRTreeVisitor* visitor ) const = 0;

		virtual const IRTExpList* children() const = 0;

	};
}
