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

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CConstructorExpression * const ñonstructorExpression )
	{
		visitUnaryNode( "ConstructorExpression", ñonstructorExpression->GetIdExpression().get() );
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

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CType * const type)
	{
		type->GetName();
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CVarDeclaration * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CVarDeclarationList * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CTrueExpression * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CFalseExpression * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CGetFieldExpression * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CConditionStatement * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CThisExpression * const )
	{
	}



	void CDotOutputVisitor::visit( AbstractTreeGenerator::COperationExpression *const operationExpression )
	{
		size_t current = enterNode( "OperationExpression" );
		operationExpression->GetLeftOperand()->Accept( this );
		addArrow( current, current + 1 );
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
		size_t rightId = nextId();
		operationExpression->GetRightOperand()->Accept( this );
		addArrow( current, rightId );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CParenExpression * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CMethodDeclaration * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CMethodDeclarationList * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CNegationExpression * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CNumberExpr * const numExpression )
	{
		size_t current = enterNode( "NumExpression" );
		addSubNode( current, numExpression->GetValue() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CExpressionList * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CIdExpression *const idExpression )
	{
		size_t current = enterNode( "IdExpression" );
		addSubNode( current, idExpression->GetName() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CIndexExpression * const )
	{
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
		// TODO 
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CArgument * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CArgumentList * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CAssignmentStatement *const assignmentStatement )
	{
		visitBinaryNode( "AssignStatement", assignmentStatement->GetIdExpression().get(),
			assignmentStatement->GetExpression().get() );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CAssignmentListStatement * const )
	{
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
		node->Accept( this );
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
	

	size_t CDotOutputVisitor::nextId()
	{
		return id + 1;
	}
}
