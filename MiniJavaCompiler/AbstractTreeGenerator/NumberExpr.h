#pragma once
#include "INode.h"
namespace AbstractTreeGenerator {
	class CNumberExpr : public IExpression {
	public:
		CNumberExpr(int val);
		~CNumberExpr();
		virtual void Accept( IVisitor*v ) override;
		const int GetValue() const;
	private:
		int value;
	};
}

