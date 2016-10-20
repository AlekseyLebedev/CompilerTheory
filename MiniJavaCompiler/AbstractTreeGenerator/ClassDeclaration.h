#pragma once
#include "IdExpression.h"
#include "ClassExtend.h"
#include "VarDeclarationList.h"
#include "MethodDeclarationList.h"
#include <memory>

namespace AbstractTreeGenerator {
	class CClassDeclaration : public INode {
	public:
		CClassDeclaration( CIdExpression* theIdExpression,
			CClassExtend* theClassExtend, 
			CVarDeclarationList* theVarDeclarationList,
			CMethodDeclarationList* theMethodDeclarationList );
		virtual ~CClassDeclaration();

		virtual void Accept(IVisitor*v) override;
		const std::shared_ptr<CIdExpression> GetIdExpression() const;
		const std::shared_ptr<CClassExtend> GetClassExtend() const;
		const std::shared_ptr<CVarDeclarationList> GetVarDeclarationList() const;
		const std::shared_ptr<CMethodDeclarationList> GetMethodDeclarationList() const;
	private:
		std::shared_ptr<CIdExpression> idExpression;
		std::shared_ptr<CClassExtend> classExtend;
		std::shared_ptr<CVarDeclarationList> varDeclarationList;
		std::shared_ptr<CMethodDeclarationList> methodDeclarationList;
	};
}
