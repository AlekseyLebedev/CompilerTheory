#pragma once
#include "IExpression.h"
#include <memory>

namespace FirstTask {
	class CNumExpression : public IExpression {
	public:
		CNumExpression( int theValue );
		virtual ~CNumExpression();
		virtual void Accept( IVisitor* ) override;
	private:
		int value;
	};
}
