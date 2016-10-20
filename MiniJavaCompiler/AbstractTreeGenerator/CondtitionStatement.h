#pragma once
#include "IdExpression.h"
#include "IStatement.h"
#include <memory>


namespace AbstractTreeGenerator {
	class CCondtitionStatement : public IStatement {
	public:
		CCondtitionStatement( std::shared_ptr<CIdExpression> theIdExpression,
			std::shared_ptr<IStatement> theStatementFirst,
			std::shared_ptr<IStatement> theStatementSecond );
		virtual ~CCondtitionStatement();

		virtual void Accept(IVisitor*V) override;
	private:
		std::shared_ptr<CIdExpression> idExpression;
		std::shared_ptr<IStatement> statementFirst;
		std::shared_ptr<IStatement> statementSecond;
	};
}
