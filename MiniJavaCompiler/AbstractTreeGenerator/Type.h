#pragma once

#include <memory>
#include "IdExpression.h"

namespace AbstractTreeGenerator {
	class CType {
	public:
		CType( std::shared_ptr<CIdExpression> theIdExpression );
		virtual ~CType();

		//		virtual void Accept(IVisitor*) override;
	private:
		std::shared_ptr<CIdExpression> idExpression;
	};
}
