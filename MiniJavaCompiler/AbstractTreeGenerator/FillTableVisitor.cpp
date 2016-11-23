#include <cassert>

#include "FillTableVisitor.h"
#include "INode.h"
#include "AllNodes.h"

extern std::shared_ptr<AbstractTreeGenerator::CStringTable> glabalStringTable;

namespace GraphvizOutput
{

	CFillTableVisitor::CFillTableVisitor() : id( 0 )
	{}

	void CFillTableVisitor::Start( SymbolTable::CClassInfo* classInfo_, SymbolTable::CMethodInfo* methodInfo_, SymbolTable::CVariableInfo* variableInfo_ )
	{
		classInfo = classInfo_;
		methodInfo = methodInfo_;
		variableInfo = variableInfo_;

		id = 0;
	}

	void CFillTableVisitor::Close()
	{}

	CFillTableVisitor::~CFillTableVisitor()
	{}

	size_t CFillTableVisitor::enterNode()
	{
		++id;
		return id;
	}

	void CFillTableVisitor::addChild( const size_t id, AbstractTreeGenerator::INode* node )
	{
		size_t next = nextId();
		if( node == 0 ) {
			enterNode();
		} else {
			node->Accept( this );
		}
	}

	void CFillTableVisitor::visitUnaryNode( AbstractTreeGenerator::INode* children )
	{
		size_t current = enterNode();
		addChild( current, children );
	}

	void CFillTableVisitor::visitBinaryNode( AbstractTreeGenerator::INode* left, AbstractTreeGenerator::INode* right )
	{
		size_t current = enterNode();
		addChild( current, left );
		addChild( current, right );
	}

	void CFillTableVisitor::visitTripleNode( AbstractTreeGenerator::INode* left, AbstractTreeGenerator::INode* center, AbstractTreeGenerator::INode* right )
	{
		size_t current = enterNode();
		addChild( current, left );
		addChild( current, center );
		addChild( current, right );
	}

	void CFillTableVisitor::visitValueNode( const std::string& value )
	{
		enterNode();
	}

	void CFillTableVisitor::visitValueNode( const int value )
	{
		enterNode();
	}

	size_t CFillTableVisitor::nextId()
	{
		return id + 1;
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CAssignmentStatement* const assignmentStatement )
	{
		visitBinaryNode(assignmentStatement->GetIdExpression().get(), assignmentStatement->GetExpression().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CClassDeclaration* const classDeclaration )
	{
		size_t id = enterNode();
		classInfo->SetIdExpression( id, classDeclaration->GetIdExpression() );
		classInfo->SetClassExtend( id, classDeclaration->GetClassExtend() );
		classInfo->SetVarDeclaration( id, classDeclaration->GetVarDeclarationList() );
		classInfo->SetMethodDeclaration( id, classDeclaration->GetMethodDeclarationList() );
		addChild( id, classDeclaration->GetIdExpression().get() );
		addChild( id, classDeclaration->GetClassExtend().get() );
		addChild( id, classDeclaration->GetVarDeclarationList().get() );
		addChild( id, classDeclaration->GetMethodDeclarationList().get() );
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

	{
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
		variableInfo->SetType( id, varDeclaration->GetType() );
		variableInfo->SetIdExpression( id, varDeclaration->GetIdExpression() );
		visitBinaryNode( varDeclaration->GetType().get(), varDeclaration->GetIdExpression().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CVarDeclarationList* const list )
	{
		visitBinaryNode( list->GetVarDeclaration().get(), list->GetVarDeclarationList().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CTrueExpression* const )
	{
		enterNode();
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CFalseExpression* const )
	{
		enterNode();
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CGetFieldExpression* const get )
	{
		visitTripleNode( get->GetIdExpression().get(), get->GetExpression().get(), get->GetExpressionList().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CConditionStatement* const condition )
	{
		visitTripleNode( condition->GetStatementFirst().get(), condition->GetExpression().get(), condition->GetStatementSecond().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CThisExpression* const )
	{
		enterNode();
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CBasicType* const type )
	{
		enterNode();
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CIdType* const type )
	{
		visitUnaryNode( type->GetIdExpression().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::COperationExpression* const operationExpression )
	{
		size_t current = enterNode();
		addChild( current, operationExpression->GetLeftOperand().get() );
		addChild( current, operationExpression->GetRightOperand().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CParenExpression* const paren )
	{
		visitUnaryNode( paren->GetExpression().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CMethodDeclaration* const method )
	{
		size_t id = enterNode();

		methodInfo->SetType( id, method->GetType().get());
		methodInfo->SetIdExpression( id, method->GetIdExpression().get());
		methodInfo->SetArgumentList( id, method->GetArgumentList().get());
		methodInfo->SetVarDeclarationList( id, method->GetVarDeclarationList().get());
		methodInfo->SetStatementList( id, method->GetStatementList().get());
		methodInfo->SetExpression( id, method->GetExpression().get() );

		addChild( id, method->GetType().get() );
		addChild( id, method->GetIdExpression().get() );
		addChild( id, method->GetArgumentList().get() );
		addChild( id, method->GetVarDeclarationList().get() );
		addChild( id, method->GetStatementList().get() );
		addChild( id, method->GetExpression().get() );
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
		visitValueNode( numExpression->GetValue() );
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
