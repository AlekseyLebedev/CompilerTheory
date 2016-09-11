#pragma once

namespace FirstTask {
	class CCompoundStatement;
	class CPrintStatement;
	class COperationExpression;
	class CNumExpression;
	class CAssignStatement;
	class CLastExpList; 
	class CIdExpression;

	__interface IVisitor {
	public:
		virtual void Visit(CIdExpression*) = 0;
		virtual void Visit(CLastExpList*) = 0;
		virtual void Visit(CAssignStatement*) = 0;		
		virtual void Visit(CCompoundStatement*) = 0;
		virtual void Visit(CPrintStatement*) = 0;
		virtual void Visit(COperationExpression*) = 0;
		virtual void Visit(CNumExpression*) = 0;
	};
}