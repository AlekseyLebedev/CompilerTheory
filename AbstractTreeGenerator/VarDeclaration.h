#pragma once

#include <memory>
#include "Type.h"
#include "IdExpression.h"

namespace FirstTask {
	class CVarDeclaration {
	public:
		CVarDeclaration( std::shared_ptr<CType> theType,
			std::shared_ptr<CIdExpression> theIdExpression );
		virtual ~CVarDeclaration();

		//		virtual void Accept(IVisitor*) override;
	private:
		std::shared_ptr<CType> type;
		std::shared_ptr<CIdExpression> idExpression;
	};
}
