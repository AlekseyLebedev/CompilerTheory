#pragma once
#include "stdafx.h"
#include "IStatemnet.h"

namespace FirstTask {
	class CAssignStatement : IStatemnet
	{
	public:
		CAssignStatement(const std::string name);
		virtual ~CAssignStatement();
		virtual void Accept(IVisitor* v) override;

		std::string GetVariableName() const;
	private:
		std::string variableName;
	};
}