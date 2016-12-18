#pragma once

#include "IRTreeClasses.h"

namespace IRTree {

	class IRTStatement
    {
	public:
		
		virtual ~IRTStatement() {};
		virtual void Accept( IRTreeVisitor* visitor ) const = 0;

	};
}