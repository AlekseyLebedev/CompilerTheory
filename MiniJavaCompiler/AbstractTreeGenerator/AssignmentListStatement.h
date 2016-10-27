#pragma once
#include "IdExpression.h"
#include "IStatement.h"
#include <memory>


namespace AbstractTreeGenerator {
	class CAssignmentListStatement : public IStatement
	{
	public:
		CAssignmentListStatement( CIdExpression* theIdExpression,
			IExpression* theExpressionFirst,
			IExpression* theExpressionSecond );
		virtual ~CAssignmentListStatement();

		virtual void Accept( IVisitor * v ) override;
		const std::shared_ptr<CIdExpression> GetIdExpression() const;
		const std::shared_ptr<IExpression> GetExpressionFirst() const;
		const std::shared_ptr<IExpression> GetExpressionSecond() const;

		
	private:
		std::shared_ptr<CIdExpression> idExpression;
		std::shared_ptr<IExpression> expressionFirst;
		std::shared_ptr<IExpression> expressionSecond;
	};
}
