#pragma once

#include <memory>
#include "VarDeclaration.h"
#include "INode.h"

namespace AbstractTreeGenerator {
	class CVarDeclarationList : public INode {
	public:
		CVarDeclarationList( CVarDeclaration* theVarDeclaration,
			CVarDeclarationList* theVarDeclarationList = nullptr );
		virtual ~CVarDeclarationList();

		virtual void Accept(IVisitor*v) override;
		const std::shared_ptr<CVarDeclaration> GetVarDeclaration() const;
		const std::shared_ptr<CVarDeclarationList> GetVarDeclarationList() const;
	private:
		std::shared_ptr<CVarDeclaration> varDeclaration;
		std::shared_ptr<CVarDeclarationList> varDeclarationList;
	};
}
