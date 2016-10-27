#pragma once

#include <memory>
#include "IdExpression.h"
#include "INode.h"

namespace AbstractTreeGenerator {
	class IType : public INode {

	};

	class CBasicType : public IType {
	public:
		CBasicType( const char* _name );
		virtual ~CBasicType() {};

		virtual void Accept( IVisitor* v ) override;
		const char* GetName() const;
	private:
		const char* name;
	};

	class CIdType : public IType {
	public:
		CIdType( CIdExpression* theIdExpression );
		virtual ~CIdType() { }

		virtual void Accept( IVisitor* v ) override;
		const std::shared_ptr<CIdExpression> GetIdExpression() const;
	private:
		std::shared_ptr<CIdExpression> idExpression;
	};


}
