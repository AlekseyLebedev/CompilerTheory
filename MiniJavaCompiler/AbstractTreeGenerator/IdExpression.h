#pragma once
#include <string>
#include "IExpression.h"

namespace AbstractTreeGenerator {
	class CIdExpression : public IExpression
	{
	public:
		CIdExpression(std::string theName);
		virtual ~CIdExpression();
		virtual void Accept(IVisitor*) override;

		std::string GetName() const;
		const std::string GetName() const;
	private:
		std::string name;
	};
}
