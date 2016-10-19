#pragma once

namespace AbstractTreeGenerator {
	class CCompoundStatement;
	class CPrintStatement;
	class COperationExpression;
	class CNumExpression;
	class CAssignStatement;
	class CLastExpressionList; 
	class CIdExpression;

	class IVisitor {
	public:
		virtual void Visit(CIdExpression*) = 0;
		virtual void Visit(CLastExpressionList*) = 0;
		virtual void Visit(CAssignStatement*) = 0;		
		virtual void Visit(CCompoundStatement*) = 0;
		virtual void Visit(CPrintStatement*) = 0;
		virtual void Visit(COperationExpression*) = 0;
		virtual void Visit(CNumExpression*) = 0;
	};
}