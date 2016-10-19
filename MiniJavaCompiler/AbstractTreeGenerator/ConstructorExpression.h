#pragma once

#include <memory>
#include "IdExpression.h"

namespace AbstractTreeGenerator {
	class CConstructorExpression : public IExpression {
	public:
		CConstructorExpression( std::shared_ptr<CIdExpression> theIdExpression );
		virtual ~CConstructorExpression();

		virtual void Accept(IVisitor*v) override;
	private:
		std::shared_ptr<CIdExpression> idExpression;
	};
}
