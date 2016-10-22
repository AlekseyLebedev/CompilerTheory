#pragma once

#include <memory>
#include "IExpression.h"

namespace AbstractTreeGenerator {
	class CFalseExpression : public IExpression {
	public:
		CFalseExpression();
		virtual ~CFalseExpression();

		virtual void Accept(IVisitor*) override;
		// возвращает значение, в данном случае false
		const bool GetBool() const;
		// возвращает значение, в данном случае false
		const bool GetValue() const;
	private:
		const bool value = false;
	};
}
