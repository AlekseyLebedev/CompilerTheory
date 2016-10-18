#pragma once
#include <string>
#include "IExpression.h"

namespace FirstTask {
	class CIdExpression : public IExpression
	{
	public:
		CIdExpression(std::string theName);
		virtual ~CIdExpression();
		virtual void Accept(IVisitor*) override;

		std::string GetName() const;
	private:
		std::string name;
	};
}
