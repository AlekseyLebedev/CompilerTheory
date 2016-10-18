#pragma once

#include <memory>
#include "IdExpression.h"

namespace FirstTask {
	class CConstructorExpression {
	public:
		CConstructorExpression( std::shared_ptr<CIdExpression> theIdExpression );
		virtual ~CConstructorExpression();

		//		virtual void Accept(IVisitor*) override;
	private:
		std::shared_ptr<CIdExpression> idExpression;
	};
}
