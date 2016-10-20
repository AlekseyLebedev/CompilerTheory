#pragma once

#include <memory>
#include "IdExpression.h"

namespace AbstractTreeGenerator {
	class CConstructorExpression : public IExpression {
	public:
		CConstructorExpression( CIdExpression* theIdExpression );
		virtual ~CConstructorExpression();

		virtual void Accept(IVisitor*v) override;

		const std::shared_ptr<CIdExpression> GetIdExpression() const;
		const std::shared_ptr<CIdExpression> GetIdExpression() const;
	private:
		std::shared_ptr<CIdExpression> idExpression;
	};
}
