#pragma once

#include <memory>
#include "VarDeclaration.h"

namespace AbstractTreeGenerator {
	class CVarDeclarationList {
	public:
		CVarDeclarationList( std::shared_ptr<CVarDeclaration> theVarDeclaration,
			std::shared_ptr<CVarDeclarationList> theVarDeclarationList = nullptr );
		virtual ~CVarDeclarationList();

		virtual void Accept(IVisitor*v) override;
	private:
		std::shared_ptr<CVarDeclaration> varDeclaration;
		std::shared_ptr<CVarDeclarationList> varDeclarationList;
	};
}
