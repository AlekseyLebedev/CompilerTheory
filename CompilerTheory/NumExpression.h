#pragma once
#include "stdafx.h"
#include "IExpression.h"

namespace FirstTask {
	class CNumExpression : public IExpression
	{
	public:
		CNumExpression(int _value);
		virtual ~CNumExpression();
		virtual void Accept(IVisitor*) override;
		int GetValue() const;
	private:
		int value;
	};
}
