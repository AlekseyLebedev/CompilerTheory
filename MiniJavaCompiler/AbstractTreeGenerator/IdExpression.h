#pragma once
#include <string>
#include "IExpression.h"

namespace AbstractTreeGenerator {
	class CIdExpression : public IExpression
	{
	public:
		CIdExpression(int theName);
		virtual ~CIdExpression();
		virtual void Accept(IVisitor*) override;

		const int GetName() const;
	private:
		int name;
	};
}
