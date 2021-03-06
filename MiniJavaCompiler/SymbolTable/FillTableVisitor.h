﻿#pragma once
#include "..\AbstractTreeGenerator\AllNodes.h"
#include "..\SymbolTable\Table.h"
#include <string>
#include <fstream>
#include <vector>

using namespace SymbolTable;

namespace SymbolTable
{

	class CFillTableVisitor : public AbstractTreeGenerator::IVisitor
	{
	public:
		CFillTableVisitor();
		virtual ~CFillTableVisitor();

		const CTable& GetTable() const;

	private:
		
		CClassInfo currentClassInfo;
		CMethodInfo currentMethodInfo;
		CVariableInfo currentVariableInfo;
		CTable table;
		bool fillingClass;
		void visitChild( AbstractTreeGenerator::INode* node );
		void visitUnaryNode( AbstractTreeGenerator::INode* children );
		void visitBinaryNode( AbstractTreeGenerator::INode* left, AbstractTreeGenerator::INode* right );
		void visitTripleNode( AbstractTreeGenerator::INode* left, AbstractTreeGenerator::INode* center, AbstractTreeGenerator::INode* right );

	public:
		// Унаследовано через IVisitor
		virtual void visit( AbstractTreeGenerator::CArgument* const ) override;
		virtual void visit( AbstractTreeGenerator::CArgumentList* const ) override;
		virtual void visit( AbstractTreeGenerator::CAssignmentListStatement* const ) override;
		virtual void visit( AbstractTreeGenerator::CAssignmentStatement* const ) override;
		virtual void visit( AbstractTreeGenerator::CClassDeclaration* const ) override;
		virtual void visit( AbstractTreeGenerator::CClassDeclarationList* const ) override;
		virtual void visit( AbstractTreeGenerator::CClassExtend* const ) override;
		virtual void visit( AbstractTreeGenerator::CCompoundStatement* const ) override;
		virtual void visit( AbstractTreeGenerator::CConstructorExpression* const ) override;
		virtual void visit( AbstractTreeGenerator::CExpressionList* const ) override;
		virtual void visit( AbstractTreeGenerator::CIdExpression* const ) override;
		virtual void visit( AbstractTreeGenerator::CIndexExpression* const ) override;
		virtual void visit( AbstractTreeGenerator::CLastExpressionList* const ) override;
		virtual void visit( AbstractTreeGenerator::CLengthExpression* const ) override;
		virtual void visit( AbstractTreeGenerator::CListConstructorExpression* const ) override;
		virtual void visit( AbstractTreeGenerator::CMainClass* const ) override;
		virtual void visit( AbstractTreeGenerator::CMethodDeclaration* const ) override;
		virtual void visit( AbstractTreeGenerator::CMethodDeclarationList* const ) override;
		virtual void visit( AbstractTreeGenerator::CNegationExpression* const ) override;
		virtual void visit( AbstractTreeGenerator::CNumberExpr* const ) override;
		virtual void visit( AbstractTreeGenerator::COperationExpression* const ) override;
		virtual void visit( AbstractTreeGenerator::CParenExpression* const ) override;
		virtual void visit( AbstractTreeGenerator::CPreconditionStatement* const ) override;
		virtual void visit( AbstractTreeGenerator::CPrintStatement* const ) override;
		virtual void visit( AbstractTreeGenerator::CProgram* const ) override;
		virtual void visit( AbstractTreeGenerator::CStatementList* const ) override;
		virtual void visit( AbstractTreeGenerator::CVarDeclaration* const ) override;
		virtual void visit( AbstractTreeGenerator::CVarDeclarationList* const ) override;
		virtual void visit( AbstractTreeGenerator::CTrueExpression* const ) override;
		virtual void visit( AbstractTreeGenerator::CFalseExpression* const ) override;
		virtual void visit( AbstractTreeGenerator::CGetFieldExpression* const ) override;
		virtual void visit( AbstractTreeGenerator::CConditionStatement* const ) override;
		virtual void visit( AbstractTreeGenerator::CThisExpression* const ) override;
		virtual void visit( AbstractTreeGenerator::CBasicType* const ) override;
		virtual void visit( AbstractTreeGenerator::CIdType* const ) override;
	};
}
