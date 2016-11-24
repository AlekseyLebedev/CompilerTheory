#pragma once
#include "IVisitor.h"

namespace AbstractTreeGenerator {
	class INode {
	public:
		virtual void Accept(IVisitor*) = 0;
		int GetCol() const;
		int GetRow() const;
		INode();


	private:
		int startCol, startRow;
	};
}