#pragma once
#include "IdExpression.h"
#include "IStatement.h"
#include <memory>


namespace AbstractTreeGenerator {
	class CAssignmentListStatement : public INode
	{
	public:
		CAssignmentListStatement( std::shared_ptr<CIdExpression> theIdExpression,
			std::shared_ptr<IExpression> theExpressionFirst,
			std::shared_ptr<IExpression> theExpressionSecond );
		virtual ~CAssignmentListStatement();

		virtual void Accept(IVisitor*) override;
	private:
		std::shared_ptr<CIdExpression> idExpression;
		std::shared_ptr<IExpression> expressionFirst;
		std::shared_ptr<IExpression> expressionSecond;
	};
}