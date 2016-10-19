#pragma once
#ifndef NUMEXPINCLUDE
#define NUMEXPINCLUDE

#include "IExpression.h"
#include <memory>

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
#endif // NUMEXPINCLUDE
