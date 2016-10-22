#pragma once

#include <memory>
#include "IExpression.h"

namespace AbstractTreeGenerator {
	class CFalseExpression : public IExpression {
	public:
		CFalseExpression();
		virtual ~CFalseExpression();

		virtual void Accept(IVisitor*) override;
		// ���������� ��������, � ������ ������ false
		const bool GetBool() const;
		// ���������� ��������, � ������ ������ false
		const bool GetValue() const;
	private:
		const bool value = false;
	};
}
