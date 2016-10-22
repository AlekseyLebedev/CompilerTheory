#include <string>
#include <cassert>

#include "DotOutputVisitor.h"
#include "INode.h"
#include "AllNodes.h"

namespace GraphvizOutput {

	CDotOutputVisitor::CDotOutputVisitor() : id( 0 )
	{
	}

	void CDotOutputVisitor::Start( std::string filename )
	{
		dotFile.open( filename, std::ios_base::out | std::ios_base::trunc );
		dotFile << "digraph G{" << std::endl;
		id = 0;
	}

	void CDotOutputVisitor::Close()
	{
		dotFile << "}" << std::endl;
		dotFile.close();
	}


	CDotOutputVisitor::~CDotOutputVisitor()
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CAssignmentStatement * const assignmentStatement )
	{
		visitBinaryNode( "AssignmentStatement", assignmentStatement->GetIdExpression().get(),
			assignmentStatement->GetExpression().get() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CClassDeclaration * const classDeclaration )
	{
		visitTripleNode( "ClassDeclaration", classDeclaration->GetIdExpression().get(),
			classDeclaration->GetClassExtend().get(), classDeclaration->GetMethodDeclarationList().get() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CClassDeclarationList * const list )
	{
		visitBinaryNode( "ClassDeclarationList", list->GetClassDeclaration().get(),
			list->GetClassDeclarationList().get() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CClassExtend * const extend )
	{
		visitUnaryNode( "ClassExtend", extend->GetIdExpression().get() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CCompoundStatement *const compoundStatement )
	{
		visitBinaryNode( "CompoundStatement", compoundStatement->GetLeftChild().get(),
			compoundStatement->GetRightChild().get() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CConstructorExpression * const сonstructorExpression )
	{
		visitUnaryNode( "ConstructorExpression", сonstructorExpression->GetIdExpression().get() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CPreconditionStatement * const precondition )
	{
		visitBinaryNode( "PreconditionStatement", precondition->GetIdExpression().get(),
			precondition->GetStatement().get() );

	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CPrintStatement *const printStatement )
	{
		visitUnaryNode( "PrintStatement", printStatement->GetExpression().get() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CProgram * const program )
	{
		visitBinaryNode( "Program", program->GetMainClass().get(),
			program->GetClassDeclarationList().get() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CStatementList * const statementList )
	{
		visitBinaryNode( "StatementList", statementList->GetStatement().get(),
			statementList->GetStatementList().get() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CType * const type )
	{
		visitValueNode( "Type", type->GetName() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CVarDeclaration * const varDeclaration )
	{
		visitBinaryNode( "VarDeclaration", varDeclaration->GetType().get(),
			varDeclaration->GetIdExpression().get() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CVarDeclarationList * const list )
	{
		visitBinaryNode( "VarDeclarationList", list->GetVarDeclaration().get(),
			list->GetVarDeclarationList().get() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CTrueExpression * const )
	{
		enterNode( "TrueExpression" );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CFalseExpression * const )
	{
		enterNode( "FalseExpression" );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CGetFieldExpression * const get )
	{
		// Слишком много get ):
		visitTripleNode( "GetFieldExpression", get->GetIdExpression().get(),
			get->GetExpression().get(), get->GetExpressionList().get() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CConditionStatement * const condition )
	{
		// TODO разабраться, что это
		visitTripleNode( "ConditionStatement", condition->GetStatementFirst().get(), condition->GetIdExpression().get(),
			condition->GetStatementSecond().get() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CThisExpression * const )
	{
		enterNode( "ThisExpression" );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::COperationExpression *const operationExpression )
	{
		size_t current = enterNode( "OperationExpression" );
		addChild( current, operationExpression->GetLeftOperand().get() );
		switch( operationExpression->GetOperationType() ) {
			case AbstractTreeGenerator::COperationExpression::Divide:
				addSubNode( current, "Divide" );
				break;
			case AbstractTreeGenerator::COperationExpression::Plus:
				addSubNode( current, "Plus" );
				break;
			case AbstractTreeGenerator::COperationExpression::Minus:
				addSubNode( current, "Minus" );
				break;
			case AbstractTreeGenerator::COperationExpression::Times:
				addSubNode( current, "Times" );
				break;
			case AbstractTreeGenerator::COperationExpression::And:
				addSubNode( current, "And" );
				break;
			case AbstractTreeGenerator::COperationExpression::Less:
				addSubNode( current, "Less" );
				break;
			case AbstractTreeGenerator::COperationExpression::Mod:
				addSubNode( current, "Mod" );
				break;
			case AbstractTreeGenerator::COperationExpression::Or:
				addSubNode( current, "Or" );
				break;
			default:
				assert( false );
		}
		addChild( current, operationExpression->GetRightOperand().get() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CParenExpression * const paren )
	{
		visitUnaryNode( "ParenExpression", paren->GetExpression().get() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CMethodDeclaration * const method )
	{
		size_t id = enterNode( "MethodDeclaration" );
		addChild( id, method->GetType().get() );
		addChild( id, method->GetIdExpression().get() );
		addChild( id, method->GetArgumentList.get() );
		addChild( id, method->GetVarDeclarationList().get() );
		addChild( id, method->GetStatementList().get() );
		addChild( id, method->GetExpression().get() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CMethodDeclarationList * const  list )
	{
		visitBinaryNode( "MethodDeclarationList", list->GetMethodDeclaration().get(),
			list->GetMethodDeclarationList().get() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CNegationExpression * const negatiation )
	{
		visitUnaryNode( "NegationExpression", negatiation->GetExpression().get() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CNumberExpr * const numExpression )
	{
		visitValueNode( "NumExpression", numExpression->GetValue() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CExpressionList * const expressionList )
	{
		visitBinaryNode( "ExpressionList", expressionList->GetExpression().get(),
			expressionList->GetExpressionList().get() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CIdExpression *const idExpression )
	{
		visitValueNode( "IdExpression", idExpression->GetName() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CIndexExpression * const index )
	{
		visitBinaryNode( "IndexExpression", index->GetEpressionFirst().get(),
			index->GetExpressionSecond().get() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CLastExpressionList *const lastExpList )
	{
		visitUnaryNode( "LastExpressionList", lastExpList->GetExpression().get() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CLengthExpression * const length )
	{
		visitUnaryNode( "LengthExpression", length->GetExpression().get() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CListConstructorExpression * const listCtor )
	{
		visitUnaryNode( "ListConstructorExpression", listCtor->GetExpression().get() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CMainClass * const main )
	{
		size_t id = enterNode( "MainClass" );
		addChild( id, main->GetClassName().get() );
		addChild( id, main->GetName().get() );
		addChild( id, main->GetArgv().get() );
		addChild( id, main->GetStatement().get() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CArgument * const argument )
	{
		visitBinaryNode( "Argument", argument->GetType().get(), argument->GetIdExpression().get() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CArgumentList * const list )
	{
		visitBinaryNode( "ArgumentList", list->GetArgument().get(), list->GetArgumentList().get() );

	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CAssignmentStatement *const assignmentStatement )
	{
		visitBinaryNode( "AssignStatement", assignmentStatement->GetIdExpression().get(),
			assignmentStatement->GetExpression().get() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CAssignmentListStatement * const assigment )
	{
		visitTripleNode( "AssignmentListStatement", assigment->GetIdExpression().get(),
			assigment->GetExpressionFirst().get(), assigment->GetExpressionSecond().get() );

	}

	size_t CDotOutputVisitor::enterNode( const std::string& label )
	{
		++id;
		dotFile << "\tn" << id << "[label=\"" << label << "\"]" << std::endl;
		return id;
	}

	void CDotOutputVisitor::addSubNode( size_t id, const std::string& label, const std::string& postfix )
	{
		dotFile << "\tn" << id << postfix << "[label=\"" << label << "\"]" << std::endl;
		dotFile << "\tn" << id << " -> n" << id << postfix << ";" << std::endl;
	}

	void CDotOutputVisitor::addSubNode( size_t id, const size_t label, const std::string& postfix )
	{
		dotFile << "\tn" << id << postfix << "[label=\"" << label << "\"]" << std::endl;
		dotFile << "\tn" << id << " -> n" << id << postfix << ";" << std::endl;
	}

	void CDotOutputVisitor::addArrow( const size_t from, const size_t to )
	{
		dotFile << "\tn" << from << " -> n" << to << ";" << std::endl;
	}

	void CDotOutputVisitor::addChild( const size_t id, AbstractTreeGenerator::INode * node )
	{
		size_t next = nextId();
		if( node == 0 ) {
			enterNode( "nullptr" );
		} else {
			node->Accept( this );
		}
		addArrow( id, next );
	}

	void CDotOutputVisitor::visitBinaryNode( const std::string & name, AbstractTreeGenerator::INode * left, AbstractTreeGenerator::INode * right )
	{
		size_t current = enterNode( name );
		addChild( current, left );
		addChild( current, right );
	}

	void CDotOutputVisitor::visitUnaryNode( const std::string & name, AbstractTreeGenerator::INode * children )
	{
		size_t current = enterNode( name );
		addChild( current, children );

	}

	void CDotOutputVisitor::visitTripleNode( const std::string & name, AbstractTreeGenerator::INode * left, AbstractTreeGenerator::INode * center, AbstractTreeGenerator::INode * right )
	{
		size_t current = enterNode( name );
		addChild( current, left );
		addChild( current, center );
		addChild( current, right );
	}

	void CDotOutputVisitor::visitValueNode( const std::string & name, const std::string & value )
	{
		size_t current = enterNode( name );
		addSubNode( current, value );
	}


	void CDotOutputVisitor::visitValueNode( const std::string & name, const int value )
	{
		size_t current = enterNode( name );
		addSubNode( current, value );
	}

	size_t CDotOutputVisitor::nextId()
	{
		return id + 1;
	}
}
