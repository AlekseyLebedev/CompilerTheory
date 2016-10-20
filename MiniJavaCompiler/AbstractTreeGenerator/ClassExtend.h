#pragma once

#include <memory>
#include "IdExpression.h"

namespace AbstractTreeGenerator {
	class CClassExtend : public INode {
	public:
		CClassExtend( CIdExpression* theIdExpression );
		virtual ~CClassExtend();

		virtual void Accept(IVisitor*V) override;
		const std::shared_ptr<CIdExpression> GetIdExpression() const;
	private:
		std::shared_ptr<CIdExpression> idExpression;
	};
}
