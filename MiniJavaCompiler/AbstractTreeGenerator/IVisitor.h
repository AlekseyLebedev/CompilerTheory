#pragma once

namespace AbstractTreeGenerator {
	class CArgument;
	class CArgumentList;
	class CAssignStatement;
	class CAssignmentListStatement;
	class CAssignmentStatement;
	class CCExpression;
	class CClassDeclaration;
	class CClassDeclarationList;
	class CClassExtend;
	class CCompoundStatement;
	class CCondtitionStatement;
	class CConstructorExpression;
	class CDotOutputVisitor;
	class CExpressionList;
	class CGraphvizLauncher;
	class CIdExpression;
	class CIndexExpression;
	class CLastExpressionList;
	class CLengthExpression;
	class CListConstructorExpression;
	class CMainClass;
	class CMethodDeclaration;
	class CMethodDeclarationList;
	class CNegationExpression;
	class CNumExpression;
	class COperationExpression;
	class CParenExpression;
	class CPreconditionStatement;
	class CPrintStatement;
	class CProgram;
	class CStatementList;
	class CType;
	class CVarDeclaration;
	class CVarDeclarationList;

	class IVisitor {
	public:
		virtual void Visit( CIdExpression* ) = 0;
		virtual void Visit( CLastExpressionList* ) = 0;
		virtual void Visit( CAssignStatement* ) = 0;
		virtual void Visit( CCompoundStatement* ) = 0;
		virtual void Visit( CPrintStatement* ) = 0;
		virtual void Visit( COperationExpression* ) = 0;
		virtual void Visit( CNumExpression* ) = 0;



		virtual void visit( CArgument* ) = 0;
		virtual void visit( CArgumentList* ) = 0;
		virtual void visit( CAssignStatement* ) = 0;
		virtual void visit( CAssignmentListStatement* ) = 0;
		virtual void visit( CAssignmentStatement* ) = 0;
		virtual void visit( CCExpression* ) = 0;
		virtual void visit( CClassDeclaration* ) = 0;
		virtual void visit( CClassDeclarationList* ) = 0;
		virtual void visit( CClassExtend* ) = 0;
		virtual void visit( CCompoundStatement* ) = 0;
		virtual void visit( CCondtitionStatement* ) = 0;
		virtual void visit( CConstructorExpression* ) = 0;
		virtual void visit( CDotOutputVisitor* ) = 0;
		virtual void visit( CExpressionList* ) = 0;
		virtual void visit( CGraphvizLauncher* ) = 0;
		virtual void visit( CIdExpression* ) = 0;
		virtual void visit( CIndexExpression* ) = 0;
		virtual void visit( CLastExpressionList* ) = 0;
		virtual void visit( CLengthExpression* ) = 0;
		virtual void visit( CListConstructorExpression* ) = 0;
		virtual void visit( CMainClass* ) = 0;
		virtual void visit( CMethodDeclaration* ) = 0;
		virtual void visit( CMethodDeclarationList* ) = 0;
		virtual void visit( CNegationExpression* ) = 0;
		virtual void visit( CNumExpression* ) = 0;
		virtual void visit( COperationExpression* ) = 0;
		virtual void visit( CParenExpression* ) = 0;
		virtual void visit( CPreconditionStatement* ) = 0;
		virtual void visit( CPrintStatement* ) = 0;
		virtual void visit( CProgram* ) = 0;
		virtual void visit( CStatementList* ) = 0;
		virtual void visit( CType* ) = 0;
		virtual void visit( CVarDeclaration* ) = 0;
		virtual void visit( CVarDeclarationList* ) = 0;
	};
}