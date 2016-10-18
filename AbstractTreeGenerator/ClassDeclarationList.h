#pragma once

#include <memory>
#include "ClassDeclaration.h"

namespace FirstTask {
	class CClassDeclarationList {
	public:
		CClassDeclarationList( std::shared_ptr<CClassDeclaration> theClassDeclaration,
			std::shared_ptr<CClassDeclarationList> theClassDeclarationList );
		virtual ~CClassDeclarationList();

		//		virtual void Accept(IVisitor*) override;
	private:
		std::shared_ptr<CClassDeclaration> classDeclaration;
		std::shared_ptr<CClassDeclarationList> classDeclarationList;
	};
}
