#pragma once

#include "IExpression.h"

namespace AbstractTreeGenerator {
	class CNumExpression : public IExpression {
	public:
		CNumExpression( int theValue );
		virtual ~CNumExpression();
		virtual void Accept( IVisitor* ) override;
	private:
		int value;
	};
}