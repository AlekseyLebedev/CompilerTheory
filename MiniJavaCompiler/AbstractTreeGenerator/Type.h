#pragma once

#include <memory>
#include "IdExpression.h"
#include "INode.h"

namespace AbstractTreeGenerator {
	class IType : public INode {
	public:
		virtual int GetType() const = 0;
	};

	enum TStandardType {
		ST_Int = -1, ST_Bool = -2, ST_Intlist = -3, ST_Void = -4, ST_StringList = -5
	};

	class CBasicType : public IType {
	public:
		CBasicType( TStandardType );
		virtual ~CBasicType() {};
		virtual int GetType() const override;
		virtual void Accept( IVisitor* v ) override;
		TStandardType GetValue() const;
	private:
		TStandardType value;
	};

	class CIdType : public IType {
	public:
		CIdType( CIdExpression* theIdExpression );
		virtual ~CIdType() {}
		virtual int GetType() const override;
		virtual void Accept( IVisitor* v ) override;
		const std::shared_ptr<CIdExpression> GetIdExpression() const;
	private:
		std::shared_ptr<CIdExpression> idExpression;
	};


}
