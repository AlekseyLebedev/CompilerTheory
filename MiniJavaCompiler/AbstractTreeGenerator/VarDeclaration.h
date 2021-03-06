#pragma once

#include <memory>
#include "Type.h"
#include "IdExpression.h"

namespace AbstractTreeGenerator {
	class CVarDeclaration : public INode {
	public:
		CVarDeclaration( IType* theType,
			CIdExpression* theIdExpression );
		virtual ~CVarDeclaration();

		virtual void Accept(IVisitor*v) override;
		const std::shared_ptr<IType> GetType() const;
		const std::shared_ptr<CIdExpression> GetIdExpression() const;
	private:
		std::shared_ptr<IType> type;
		std::shared_ptr<CIdExpression> idExpression;
	};
}
