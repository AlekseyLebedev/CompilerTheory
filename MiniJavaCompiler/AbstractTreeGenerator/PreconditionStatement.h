#pragma once
#include "IdExpression.h"
#include "IStatement.h"
#include <memory>


namespace AbstractTreeGenerator {
	class CPreconditionStatement : public IStatement {
	public:
		CPreconditionStatement( IExpression* theExpression,
			IStatement* theStatement );
		virtual ~CPreconditionStatement();

		virtual void Accept(IVisitor*v) override;
		const std::shared_ptr<IExpression> GetExpression() const;
		const std::shared_ptr<IStatement> GetStatement() const;
	private:
		std::shared_ptr<IExpression> expression;
		std::shared_ptr<IStatement> statement;
	};
}
