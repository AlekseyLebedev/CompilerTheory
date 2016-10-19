#pragma once
#include "IVisitor.h"

namespace AbstractTreeGenerator {
	class INode {
	public:
		virtual void Accept(IVisitor*) = 0;
	};
}