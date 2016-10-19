#pragma once

#include <memory>
#include "ClassDeclaration.h"

namespace AbstractTreeGenerator {
	class CClassDeclarationList : public INode {
	public:
		CClassDeclarationList( std::shared_ptr<CClassDeclaration> theClassDeclaration,
			std::shared_ptr<CClassDeclarationList> theClassDeclarationList = nullptr );
		virtual ~CClassDeclarationList();

		virtual void Accept(IVisitor*V) override;
	private:
		std::shared_ptr<CClassDeclaration> classDeclaration;
		std::shared_ptr<CClassDeclarationList> classDeclarationList;
	};
}
