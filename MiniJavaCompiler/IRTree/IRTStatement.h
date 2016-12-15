#pragma once

#include "IRTreeClasses.h"

namespace IRTree {

	class IRTStatement : public IRTNode
    {
	public:
		
		virtual ~IRTStatement() {};
		virtual void Accept( IRTreeVisitor* visitor ) const = 0;
		virtual const IRTExpList* children() const = 0;

	};
}
