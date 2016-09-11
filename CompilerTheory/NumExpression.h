#pragma once
#include "stdafx.h"
#include "IExpression.h"

namespace FirstTask {
	class CNumExpression : public IExpression
	{
	public:
		CNumExpression(int _value);
		virtual ~CNumExpression();

	private:
		int value;
	};
}
