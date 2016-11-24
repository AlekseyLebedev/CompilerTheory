#include <string>
#include <cassert>

#include "FillTableVisitor.h"

extern std::shared_ptr<AbstractTreeGenerator::CStringTable> glabalStringTable;

namespace SymbolTable
{

	CFillTableVisitor::CFillTableVisitor()
	{
		assert( false );
	}

	CFillTableVisitor::~CFillTableVisitor()
	{
		assert( false );
	}

	const CTable& CFillTableVisitor::GetTable() const
	{
		return table;
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
		assert( false );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CClassDeclaration* const classDeclaration )
	{
		int id = classDeclaration->GetIdExpression()->GetName();
		currentClassInfo = CClassInfo( id );
		
		if( classDeclaration->GetClassExtend() != 0 ) {
			currentClassInfo.SetExtend( classDeclaration->GetClassExtend()->GetIdExpression()->GetName() );
		}

		visitChild( classDeclaration->GetMethodDeclarationList().get() );
		visitChild( classDeclaration->GetVarDeclarationList().get() );

		table.AddClassInfo( classDeclaration->GetIdExpression()->GetName(), currentClassInfo );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CClassDeclarationList* const list )
	{
		visitBinaryNode( list->GetClassDeclaration().get(), list->GetClassDeclarationList().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CClassExtend* const extend )
	{
		assert( false );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CCompoundStatement* const compoundStatement )
	{
		assert( false );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CConstructorExpression* const сonstructorExpression )
	{
		assert( false );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CPreconditionStatement* const precondition )
	{
		assert( false );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CPrintStatement* const printStatement )
	{
		assert( false );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CProgram* const program )
	{
		visitBinaryNode( program->GetMainClass().get(), program->GetClassDeclarationList().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CStatementList* const statementList )
	{
		assert( false );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CVarDeclaration* const varDeclaration )
	{
		assert( false );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CVarDeclarationList* const list )
	{
		currentMethodInfo.AddVariableInfo( list->GetVarDeclaration()->GetIdExpression()->GetName(),
			list->GetVarDeclaration()->GetType()->GetType() );
		visitChild( list->GetVarDeclarationList().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CTrueExpression* const )
	{
		assert( false );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CFalseExpression* const )
	{
		assert( false );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CGetFieldExpression* const get )
	{
		assert( false );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CConditionStatement* const condition )
	{
		assert( false );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CThisExpression* const )
	{
		assert( false );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CBasicType* const type )
	{
		assert( false );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CIdType* const type )
	{
		assert( false );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::COperationExpression* const operationExpression )
	{
		assert( false );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CParenExpression* const paren )
	{
		assert( false );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CMethodDeclaration* const method )
	{
		currentMethodInfo = CMethodInfo();
		currentArguments.clear();
		visitChild( method->GetArgumentList().get() );
		currentMethodInfo.SetArguments( currentArguments );
		currentMethodInfo.SetReturnType( method->GetType()->GetType() );
		visitChild( method->GetVarDeclarationList().get() );
		currentClassInfo.InsertMethod( method->GetIdExpression()->GetName() , currentMethodInfo );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CMethodDeclarationList* const  list )
	{
		visitBinaryNode( list->GetMethodDeclaration().get(), list->GetMethodDeclarationList().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CNegationExpression* const negatiation )
	{
		assert( false );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CNumberExpr* const numExpression )
	{
		assert( false );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CExpressionList* const expressionList )
	{
		assert( false );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CIdExpression* const idExpression )
	{
		assert( false );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CIndexExpression* const index )
	{
		assert( false );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CLastExpressionList* const lastExpList )
	{
		assert( false );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CLengthExpression* const length )
	{
		assert( false );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CListConstructorExpression* const listCtor )
	{
		assert( false );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CMainClass* const main )
	{
		currentClassInfo = CClassInfo();
		currentMethodInfo = CMethodInfo();
		currentArguments.clear();
		currentArguments.push_back( AbstractTreeGenerator::TStandardType::ST_StringList );
		currentMethodInfo.SetArguments( currentArguments );
		currentMethodInfo.SetReturnType( AbstractTreeGenerator::TStandardType::ST_Void );
		assert( glabalStringTable->insert( "main" ) == 0 );
		currentClassInfo.InsertMethod( 0, currentMethodInfo );
		table.AddClassInfo( main->GetClassName()->GetName(), currentClassInfo );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CArgument* const argument )
	{
		currentArguments.push_back( argument->GetType()->GetType() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CArgumentList* const list )
	{
		visitBinaryNode( list->GetArgument().get(), list->GetArgumentList().get() );
	}

	void CFillTableVisitor::visit( AbstractTreeGenerator::CAssignmentListStatement* const assigment )
	{
		assert( false );
	}
}
