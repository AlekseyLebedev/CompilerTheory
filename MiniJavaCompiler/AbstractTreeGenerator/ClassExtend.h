#pragma once

#include <memory>
#include "IdExpression.h"

namespace AbstractTreeGenerator {
	class CClassExtend {
	public:
		CClassExtend( std::shared_ptr<CIdExpression> theIdExpression );
		virtual ~CClassExtend();

		//		virtual void Accept(IVisitor*) override;
	private:
		std::shared_ptr<CIdExpression> idExpression;
	};
}
