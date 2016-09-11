#pragma once
#include "stdafx.h"
#include "IStatemnet.h"
#include "IExpression.h"
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