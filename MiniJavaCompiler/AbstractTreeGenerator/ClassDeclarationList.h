#pragma once

#include <memory>
#include "ClassDeclaration.h"

namespace AbstractTreeGenerator {
	class CClassDeclarationList : public INode {
	public:
		CClassDeclarationList( CClassDeclaration* theClassDeclaration,
			CClassDeclarationList* theClassDeclarationList = nullptr );
		virtual ~CClassDeclarationList();

		virtual void Accept(IVisitor*V) override;
		const std::shared_ptr<CClassDeclaration> GetClassDeclaration() const;
		const std::shared_ptr<CClassDeclarationList> GetClassDeclarationList() const;
	private:
		std::shared_ptr<CClassDeclaration> classDeclaration;
		std::shared_ptr<CClassDeclarationList> classDeclarationList;
	};
}
