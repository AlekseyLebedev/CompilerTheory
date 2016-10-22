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
		size_t current = enterNode( "AssignmentStatement" );
		assignmentStatement->GetIdExpression()->Accept( this );
		addArrrow( current, current + 1 );
		size_t rightId = nextId();
		assignmentStatement->GetExpression()->Accept( this );
		addArrrow( current, rightId );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CClassDeclaration * const classDeclaration )
	{
		size_t current = enterNode( "ClassDeclaration" );
		classDeclaration->GetIdExpression()->Accept( this );
		addArrrow( current, current + 1 );
		size_t rightId = nextId();
		classDeclaration->GetClassExtend()->Accept( this );
		addArrrow( current, current + 1 );
		auto list = classDeclaration->GetMethodDeclarationList();
		rightId = nextId();
		list->Accept( this );
		addArrrow( current, rightId );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CClassDeclarationList * const list )
	{
		size_t current = enterNode( "ClassDeclarationList" );
		list->GetClassDeclaration()->Accept( this );
		addArrrow( current, current + 1 );
		size_t rightId = nextId();
		list->GetClassDeclarationList()->Accept( this );
		addArrrow( current, rightId );
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CClassExtend * const extend )
	{
		size_t current = enterNode( "ClassExtend" );
		extend->GetIdExpression()->Accept( this );
		addArrrow( current, current + 1 );
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

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CStatementList * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CType * const )
	{
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
		addArrrow( current, current + 1 );
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
		addArrrow( current, rightId );
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

	void CDotOutputVisitor::addArrrow( const size_t from, const size_t to )
	{
		dotFile << "\tn" << from << " -> n" << to << ";" << std::endl;
	}

	void CDotOutputVisitor::visitBinaryNode( const std::string & name, AbstractTreeGenerator::INode * left, AbstractTreeGenerator::INode * right )
	{
		size_t current = enterNode( name );
		left->Accept( this );
		addArrrow( current, current + 1 );
		size_t rightId = nextId();
		right->Accept( this );
		addArrrow( current, rightId );
	}

	void CDotOutputVisitor::visitUnaryNode( const std::string & name, AbstractTreeGenerator::INode * children )
	{
		size_t current = enterNode( name );
		children->Accept( this );
		addArrrow( current, current + 1 );

	}

	size_t CDotOutputVisitor::nextId()
	{
		return id + 1;
	}
}
