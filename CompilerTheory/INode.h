#pragma once
#include "IVisitor.h"

namespace FirstTask {
	__interface INode {
		virtual void Accept(IVisitor*) = 0;
	};
}