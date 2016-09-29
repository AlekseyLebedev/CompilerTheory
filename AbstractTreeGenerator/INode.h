#pragma once
#include "IVisitor.h"

namespace FirstTask {
	class INode {
	public:
		virtual void Accept(IVisitor*) = 0;
	};
}