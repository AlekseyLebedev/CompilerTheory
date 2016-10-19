#pragma once

#include <memory>
#include "Type.h"
#include "IdExpression.h"
#include "ArgumentList.h"
#include "VarDeclarationList.h"
#include "StatementList.h"
#include "IExpression.h"

namespace AbstractTreeGenerator {
	class CMethodDeclaration {
	public:
		CMethodDeclaration( std::shared_ptr<CType> theType, 
			std::shared_ptr<CIdExpression> theIdExpression, 
			std::shared_ptr<CArgumentList> theArgumentList, 
			std::shared_ptr<CVarDeclarationList>  theVarDeclarationList,
			std::shared_ptr<IExpression> theExpression );
		virtual ~CMethodDeclaration();

		//		virtual void Accept(IVisitor*) override;
	private:
		std::shared_ptr<CType> type;
		std::shared_ptr<CIdExpression> idExpression;
		std::shared_ptr<CArgumentList> argumentList;
		std::shared_ptr<CVarDeclarationList>  varDeclarationList;
		std::shared_ptr<IExpression> expression;
	};
}
