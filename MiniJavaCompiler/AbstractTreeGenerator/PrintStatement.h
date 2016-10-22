#pragma once

#include "IStatement.h"
#include "IExpression.h"
#include <memory>

namespace AbstractTreeGenerator {
	class CPrintStatement : public IStatement
	{
	public:
		CPrintStatement(IExpression* _expression);
		virtual ~CPrintStatement();
		virtual void Accept(IVisitor*) override;

		const std::shared_ptr<IExpression> GetExpression() const;
	private:
		std::shared_ptr<IExpression> expression;
	};
}
