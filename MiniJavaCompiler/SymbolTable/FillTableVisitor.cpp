#include <string>
#include <cassert>

#include "FillTableVisitor.h"

extern std::shared_ptr<AbstractTreeGenerator::CStringTable> glabalStringTable;

namespace SymbolTable
{

	CFillTableVisitor::CFillTableVisitor()
	{
	}

	CFillTableVisitor::~CFillTableVisitor()
	{
	}

	void CFillTableVisitor::visitChild( AbstractTreeGenerator::INode* node )
	{
		if( node != 0 ) {
			node->Accept( this );
		}
	}

	void CFillTableVisitor::visitUnaryNode( AbstractTreeGenerator::INode* children )
	{
		visitChild( children );
	}

	void CFillTableVisitor::visitBinaryNode( AbstractTreeGenerator::INode* left, AbstractTreeGenerator::INode* right )
	{
		visitChild( left );
		visitChild( right );
	}

	void CFillTableVisitor::visitTripleNode( AbstractTreeGenerator::INode* left, AbstractTreeGenerator::INode* center, AbstractTreeGenerator::INode* right )
	{
		visitChild( left );
		visitChild( center );
		visitChild( right );
	}


	void CFillTableVisitor::visit( AbstractTreeGenerator::CAssignmentStatement* const assignmentStatement )
	{
		visitBinaryNode( assignmentStatement->GetIdExpression().get(), assignmentStatement->GetExpression().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CClassDeclaration* const classDeclaration )
	{
		
		classInfo->SetIdExpression( classDeclaration->GetIdExpression() );
		classInfo->SetClassExtend( classDeclaration->GetClassExtend() );
		classInfo->SetVarDeclaration( classDeclaration->GetVarDeclarationList() );
		classInfo->SetMethodDeclaration( classDeclaration->GetMethodDeclarationList() );
		visitChild( classDeclaration->GetIdExpression().get() );
		visitChild( classDeclaration->GetClassExtend().get() );
		visitChild( classDeclaration->GetVarDeclarationList().get() );
		visitChild( classDeclaration->GetMethodDeclarationList().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CClassDeclarationList* const list )
	{
		visitBinaryNode( list->GetClassDeclaration().get(), list->GetClassDeclarationList().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CClassExtend* const extend )
	{
		visitUnaryNode( extend->GetIdExpression().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CCompoundStatement* const compoundStatement )
	{
		visitBinaryNode( compoundStatement->GetLeftChild().get(), compoundStatement->GetRightChild().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CConstructorExpression* const сonstructorExpression )
	{
		visitUnaryNode( сonstructorExpression->GetIdExpression().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CPreconditionStatement* const precondition )
	{
		visitBinaryNode( precondition->GetExpression().get(), precondition->GetStatement().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CPrintStatement* const printStatement )
	{
		visitUnaryNode( printStatement->GetExpression().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CProgram* const program )
	{
		visitBinaryNode( program->GetMainClass().get(), program->GetClassDeclarationList().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CStatementList* const statementList )
	{
		visitBinaryNode( statementList->GetStatement().get(), statementList->GetStatementList().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CVarDeclaration* const varDeclaration )
	{
		variableInfo->SetType( varDeclaration->GetType() );
		variableInfo->SetIdExpression( varDeclaration->GetIdExpression() );
		visitBinaryNode( varDeclaration->GetType().get(), varDeclaration->GetIdExpression().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CVarDeclarationList* const list )
	{
		visitBinaryNode( list->GetVarDeclaration().get(), list->GetVarDeclarationList().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CTrueExpression* const )
	{
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CFalseExpression* const )
	{
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CGetFieldExpression* const get )
	{
		// Слишком много get ):
		visitTripleNode( get->GetIdExpression().get(), get->GetExpression().get(), get->GetExpressionList().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CConditionStatement* const condition )
	{
		// TODO разабраться, что это
		visitTripleNode( condition->GetStatementFirst().get(), condition->GetExpression().get(), condition->GetStatementSecond().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CThisExpression* const )
	{
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CBasicType* const type )
	{
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CIdType* const type )
	{
		visitUnaryNode( type->GetIdExpression().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::COperationExpression* const operationExpression )
	{
		visitChild( current, operationExpression->GetLeftOperand().get() );
		visitChild( current, operationExpression->GetRightOperand().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CParenExpression* const paren )
	{
		visitUnaryNode( paren->GetExpression().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CMethodDeclaration* const method )
	{
		methodInfo->SetType( method->GetType().get() );
		methodInfo->SetIdExpression( method->GetIdExpression().get() );
		methodInfo->SetArgumentList( method->GetArgumentList().get() );
		methodInfo->SetVarDeclarationList( method->GetVarDeclarationList().get() );
		methodInfo->SetStatementList( method->GetStatementList().get() );
		methodInfo->SetExpression( method->GetExpression().get() );

		visitChild( method->GetType().get() );
		visitChild( method->GetIdExpression().get() );
		visitChild( method->GetArgumentList().get() );
		visitChild( method->GetVarDeclarationList().get() );
		visitChild( method->GetStatementList().get() );
		visitChild( method->GetExpression().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CMethodDeclarationList* const  list )
	{
		visitBinaryNode( list->GetMethodDeclaration().get(), list->GetMethodDeclarationList().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CNegationExpression* const negatiation )
	{
		visitUnaryNode( negatiation->GetExpression().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CNumberExpr* const numExpression )
	{
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CExpressionList* const expressionList )
	{
		visitBinaryNode( expressionList->GetExpression().get(), expressionList->GetExpressionList().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CIdExpression* const idExpression )
	{
		visitValueNode( idExpression->GetName() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CIndexExpression* const index )
	{
		visitBinaryNode( index->GetEpressionFirst().get(), index->GetExpressionSecond().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CLastExpressionList* const lastExpList )
	{
		visitUnaryNode( lastExpList->GetExpression().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CLengthExpression* const length )
	{
		visitUnaryNode( length->GetExpression().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CListConstructorExpression* const listCtor )
	{
		visitUnaryNode( listCtor->GetExpression().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CMainClass* const main )
	{
		visitTripleNode( main->GetClassName().get(), main->GetArgv().get(), main->GetStatement().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CArgument* const argument )
	{
		visitBinaryNode( argument->GetType().get(), argument->GetIdExpression().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CArgumentList* const list )
	{
		visitBinaryNode( list->GetArgument().get(), list->GetArgumentList().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CAssignmentListStatement* const assigment )
	{
		visitTripleNode( assigment->GetIdExpression().get(), assigment->GetExpressionFirst().get(), assigment->GetExpressionSecond().get() );
	}
}
