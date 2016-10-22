#pragma once

#include <memory>
#include "IExpression.h"

namespace AbstractTreeGenerator {
	class CTrueExpression : public IExpression {
	public:
		CTrueExpression();
		virtual ~CTrueExpression();

		virtual void Accept(IVisitor*) override;
		// ���������� ��������, � ������ ������ true
		const bool GetBool() const;
		// ���������� ��������, � ������ ������ true
		const bool GetValue() const;
	private:
		const bool value = true;
	};
}
