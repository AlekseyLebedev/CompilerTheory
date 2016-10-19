#pragma once

#include "IExpression.h"

namespace AbstractTreeGenerator {
	class CNumberExpression : public IExpression {
	public:
		CNumberExpression( int theValue );
		virtual ~CNumberExpression();
		virtual void Accept( IVisitor* ) override;
	private:
		int value;
	};
}