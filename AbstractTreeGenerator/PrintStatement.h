#pragma once

#include "IStatemnet.h"
#include "IExpression.h"
#include <memory>

namespace FirstTask {
	class CPrintStatement : public IStatemnet
	{
	public:
		CPrintStatement(std::shared_ptr<IExpression> _expression);
		virtual ~CPrintStatement();
		virtual void Accept(IVisitor*) override;

		std::shared_ptr<IExpression> GetExpression() const;
	private:
		std::shared_ptr<IExpression> expression;
	};
}