#pragma once

#include <memory>
#include "MethodDeclaration.h"

namespace AbstractTreeGenerator {
	class CMethodDeclarationList : public INode {
	public:
		CMethodDeclarationList( std::shared_ptr<CMethodDeclaration> theMethodDeclaration,
			std::shared_ptr<CMethodDeclarationList> theMethodDeclarationList = nullptr );
		virtual ~CMethodDeclarationList();

		virtual void Accept(IVisitor*v) override;
	private:
		std::shared_ptr<CMethodDeclaration> methodDeclaration;
		std::shared_ptr<CMethodDeclarationList> methodDeclarationList;
	};
}
