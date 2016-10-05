#pragma once
#include <string>
#include <memory>
#include "IStatemnet.h"
#include "IExpression.h"

namespace FirstTask {
	class CAssignStatement : public IStatemnet
	{
	public:
		CAssignStatement(const std::string name, std::shared_ptr<IExpression> operation);
		virtual ~CAssignStatement();
		virtual void Accept(IVisitor* v) override;

		std::string GetVariableName() const;
		std::shared_ptr<IExpression> GetExpression() const;
	private:
		std::string variableName;
		std::shared_ptr<IExpression> expression;
	};
}