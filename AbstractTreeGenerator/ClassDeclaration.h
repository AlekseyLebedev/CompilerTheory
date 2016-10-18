#pragma once

#include <memory>
#include "ClassDeclarationList.h"

namespace FirstTask {
	class CClassDeclaration {
	public:
		CClassDeclaration( std::shared_ptr<CClassDeclaration> theClassDeclaration,
			std::shared_ptr<CClassDeclarationList> theClassDeclarationList = nullptr );
		virtual ~CClassDeclaration();

		//		virtual void Accept(IVisitor*) override;
	private:
		std::shared_ptr<CClassDeclaration> classDeclaration;
		std::shared_ptr<CClassDeclarationList> classDeclarationList;
	};
}
