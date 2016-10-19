#pragma once
#include "IdExpression.h"
#include "IStatement.h"
#include <memory>


namespace AbstractTreeGenerator {
	class CondtitionStatement : public IStatement {
	public:
		CondtitionStatement( std::shared_ptr<CIdExpression> theIdExpression,
			std::shared_ptr<IStatement> theStatementFirst,
			std::shared_ptr<IStatement> theStatementSecond );
		virtual ~CondtitionStatement();

		//		virtual void Accept(IVisitor*) override;
	private:
		std::shared_ptr<CIdExpression> idExpression;
		std::shared_ptr<IStatement> statementFirst;
		std::shared_ptr<IStatement> statementSecond;
	};
}
