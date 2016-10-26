#pragma once

#include <memory>
#include "Type.h"
#include "IdExpression.h"
#include "ArgumentList.h"
#include "VarDeclarationList.h"
#include "StatementList.h"
#include "IExpression.h"

namespace AbstractTreeGenerator {
	class CMethodDeclaration : public INode {
	public:
		CMethodDeclaration( IType* theType,
			CIdExpression* theIdExpression,
			CArgumentList* theArgumentList,
			CVarDeclarationList*  theVarDeclarationList,
			CStatementList*  theStatementList,
			IExpression* theExpression );
		virtual ~CMethodDeclaration();

		virtual void Accept( IVisitor*v ) override;
		const std::shared_ptr<IType> GetType() const;
		const std::shared_ptr<CIdExpression> GetIdExpression() const;
		const std::shared_ptr<CArgumentList> GetArgumentList() const;
		const std::shared_ptr<CVarDeclarationList> GetVarDeclarationList() const;
		const std::shared_ptr<CStatementList> GetStatementList() const;
		const std::shared_ptr<IExpression> GetExpression() const;
	private:
		std::shared_ptr<IType> type;
		std::shared_ptr<CIdExpression> idExpression;
		std::shared_ptr<CArgumentList> argumentList;
		std::shared_ptr<CVarDeclarationList>  varDeclarationList;
		std::shared_ptr<CStatementList>  statementList;
		std::shared_ptr<IExpression> expression;
	};
}
