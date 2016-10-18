#pragma once

#include <memory>
#include "ClassDeclarationList.h"

namespace FirstTask {
	class CClassDeclaration {
	public:
		CClassDeclaration( );
		virtual ~CClassDeclaration();

		//		virtual void Accept(IVisitor*) override;
	private:
		std::shared_ptr<CClassDeclaration> classDeclaration;
		std::shared_ptr<CClassDeclarationList> classDeclarationList;
	};
}
