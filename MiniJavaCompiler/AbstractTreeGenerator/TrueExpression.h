#pragma once

#include <memory>
#include "IExpression.h"

namespace AbstractTreeGenerator {
	class CTrueExpression : public IExpression {
	public:
		CTrueExpression();
		virtual ~CTrueExpression();

		virtual void Accept(IVisitor*) override;
	private:
		const bool value = true;
	};
}