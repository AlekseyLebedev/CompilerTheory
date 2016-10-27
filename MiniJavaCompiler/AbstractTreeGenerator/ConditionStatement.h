#pragma once
#include "IdExpression.h"
#include "IStatement.h"
#include <memory>


namespace AbstractTreeGenerator {
	class CConditionStatement : public IStatement {
	public:
		CConditionStatement( IExpression* theExpression,
			IStatement* theStatementFirst,
			IStatement* theStatementSecond );
		virtual ~CConditionStatement();

		virtual void Accept(IVisitor*V) override;
		const std::shared_ptr<IExpression> GetExpression() const;
		const std::shared_ptr<IStatement> GetStatementFirst() const;
		const std::shared_ptr<IStatement> GetStatementSecond() const;
	private:
		std::shared_ptr<IExpression> expression;
		std::shared_ptr<IStatement> statementFirst;
		std::shared_ptr<IStatement> statementSecond;
	};
}
