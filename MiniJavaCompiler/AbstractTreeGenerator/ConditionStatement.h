#pragma once
#include "IdExpression.h"
#include "IStatement.h"
#include <memory>


namespace AbstractTreeGenerator {
	class CConditionStatement : public IStatement {
	public:
		CConditionStatement( std::shared_ptr<CIdExpression> theIdExpression,
			std::shared_ptr<IStatement> theStatementFirst,
			std::shared_ptr<IStatement> theStatementSecond );
		virtual ~CConditionStatement();

		virtual void Accept(IVisitor*V) override;
	private:
		std::shared_ptr<CIdExpression> idExpression;
		std::shared_ptr<IStatement> statementFirst;
		std::shared_ptr<IStatement> statementSecond;
	};
}
