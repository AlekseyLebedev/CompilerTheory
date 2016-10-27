#pragma once

#include <memory>
#include "MethodDeclaration.h"

namespace AbstractTreeGenerator {
	class CMethodDeclarationList : public INode {
	public:
		CMethodDeclarationList( CMethodDeclaration* theMethodDeclaration,
			CMethodDeclarationList* theMethodDeclarationList = nullptr );
		virtual ~CMethodDeclarationList();

		virtual void Accept( IVisitor*v ) override;
		const std::shared_ptr<CMethodDeclaration> GetMethodDeclaration() const;
		const std::shared_ptr<CMethodDeclarationList> GetMethodDeclarationList() const;
	private:
		std::shared_ptr<CMethodDeclaration> methodDeclaration;
		std::shared_ptr<CMethodDeclarationList> methodDeclarationList;
	};
}
