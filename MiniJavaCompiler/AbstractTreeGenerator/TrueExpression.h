#pragma once

#include <memory>
#include "IExpression.h"

namespace AbstractTreeGenerator {
	class CTrueExpression : public IExpression {
	public:
		CTrueExpression();
		virtual ~CTrueExpression();

		virtual void Accept(IVisitor*) override;
		// возвращает значение, в данном случае true
		const bool GetBool() const;
		// возвращает значение, в данном случае true
		const bool GetValue() const;
	private:
		const bool value = true;
	};
}
