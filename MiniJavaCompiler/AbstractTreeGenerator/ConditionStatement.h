#pragma once
#include "IdExpression.h"
#include "IStatement.h"
#include <memory>


namespace AbstractTreeGenerator {
	class CConditionStatement : public IStatement {
	public:
		CConditionStatement( CIdExpression* theIdExpression,
			IStatement* theStatementFirst,
			IStatement* theStatementSecond );
		virtual ~CConditionStatement();

		virtual void Accept(IVisitor*V) override;
		const std::shared_ptr<CIdExpression> GetIdExpression() const;
		const std::shared_ptr<IStatement> GetStatementFirst() const;
		const std::shared_ptr<IStatement> GetStatementSecond() const;
	private:
		std::shared_ptr<CIdExpression> idExpression;
		std::shared_ptr<IStatement> statementFirst;
		std::shared_ptr<IStatement> statementSecond;
	};
}
