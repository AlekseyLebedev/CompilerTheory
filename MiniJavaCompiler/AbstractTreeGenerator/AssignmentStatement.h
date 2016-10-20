#pragma once
#include "IdExpression.h"
#include "IStatement.h"
#include <memory>


namespace AbstractTreeGenerator {
	class CAssignmentStatement : public IStatement {
	public:
		CAssignmentStatement( CIdExpression* theIdExpression,
			IExpression* theExpression );
		virtual ~CAssignmentStatement();

		virtual void Accept( IVisitor* v ) override;

		const std::shared_ptr<CIdExpression> GetIdExpression() const;
		const std::shared_ptr<IExpression> GetExpression() const;

		const std::shared_ptr<CIdExpression> GetIdExpression() const;
		const std::shared_ptr<IExpression> GetExpression() const;
		const std::shared_ptr<CIdExpression> GetIdExpression() const;
		const std::shared_ptr<IExpression> GetExpression() const;
	private:
		std::shared_ptr<CIdExpression> idExpression;
		std::shared_ptr<IExpression> expression;
	};
}
