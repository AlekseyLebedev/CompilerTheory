#pragma once
#include "stdafx.h"
#include "IExpression.h"

namespace FirstTask {
	class CIdExpression : public IExpression
	{
	public:
		CIdExpression(std::string _name);
		virtual ~CIdExpression();
		virtual void Accept(IVisitor*) override;

		std::string GetName() const;
	private:
		std::string name;
	};
}
