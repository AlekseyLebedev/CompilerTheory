#pragma once

#include <memory>
#include "MethodDeclaration.h"

namespace FirstTask {
	class CMethodDeclarationList {
	public:
		CMethodDeclarationList( std::shared_ptr<CMethodDeclaration> theMethodDeclaration,
			std::shared_ptr<CMethodDeclarationList> theMethodDeclarationList = nullptr );
		virtual ~CMethodDeclarationList();

		//		virtual void Accept(IVisitor*) override;
	private:
		std::shared_ptr<CMethodDeclaration> methodDeclaration;
		std::shared_ptr<CMethodDeclarationList> methodDeclarationList;
	};
}
