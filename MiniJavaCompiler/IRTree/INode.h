#pragma once

#include "IVisitor.h"

namespace IRTree {
	class INode {
	public:
		virtual void Accept( IVisitor* visitor ) const = 0;
	};
}