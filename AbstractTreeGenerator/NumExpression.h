#pragma once
#include "IExpression.h"
#include "INTEGER_LITERAL.h"
#include <memory>

namespace FirstTask {
	class CNumExpression : public IExpression {
	public:
		CNumExpression( std::shared_ptr<CINTEGER_LITERAL> theValue );
		CNumExpression( int theValue );
		virtual ~CNumExpression();
		virtual void Accept( IVisitor* ) override;
		std::shared_ptr<CINTEGER_LITERAL> GetValue() const;
	private:
		std::shared_ptr<CINTEGER_LITERAL> value;
		int value;
	};
}
