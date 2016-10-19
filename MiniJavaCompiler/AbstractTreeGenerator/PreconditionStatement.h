#pragma once
#include "IdExpression.h"
#include "IStatement.h"
#include <memory>


namespace AbstractTreeGenerator {
	class CPreconditionStatement : public IStatement {
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
