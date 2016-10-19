#pragma once

#include <memory>
#include "IdExpression.h"
#include "INode.h"

namespace AbstractTreeGenerator {
	class CType : INode {
	public:
		CType( std::shared_ptr<CIdExpression> theIdExpression );
		virtual ~CType();

		virtual void Accept(IVisitor* v) override;
	private:
		std::shared_ptr<CIdExpression> idExpression;
	};
}
