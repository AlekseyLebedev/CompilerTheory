#pragma once

#include <memory>
#include "VarDeclaration.h"

namespace FirstTask {
	class CVarDeclarationList {
	public:
		CVarDeclarationList( std::shared_ptr<CVarDeclaration> theVarDeclaration,
			std::shared_ptr<CVarDeclarationList> theVarDeclarationList );
		virtual ~CVarDeclarationList();

		//		virtual void Accept(IVisitor*) override;
	private:
		std::shared_ptr<CVarDeclaration> varDeclaration;
		std::shared_ptr<CVarDeclarationList> varDeclarationList;
	};
}
