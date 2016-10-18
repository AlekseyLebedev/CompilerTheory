#pragma once
#include "IdExpression.h"
#include "IStatement.h"
#include <memory>


namespace FirstTask {
	class CPreconditionStatement {
	public:
		CPreconditionStatement( std::shared_ptr<CIdExpression> theIdExpression,
			std::shared_ptr<IStatement> theStatement );
		virtual ~CPreconditionStatement();

		//		virtual void Accept(IVisitor*) override;
	private:
		std::shared_ptr<CIdExpression> idExpression;
		std::shared_ptr<IStatement> statement;
	};
}
