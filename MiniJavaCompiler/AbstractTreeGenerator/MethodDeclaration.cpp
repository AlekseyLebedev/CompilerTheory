#include "MethodDeclaration.h"

AbstractTreeGenerator::CMethodDeclaration::CMethodDeclaration( CType* theType,
	CIdExpression* theIdExpression,
	CArgumentList* theArgumentList,
	CVarDeclarationList*  theVarDeclarationList,
	CStatementList*  theStatementList,
	IExpression* theExpression ) :
	type( theType ), idExpression( theIdExpression ), argumentList( theArgumentList ),
	varDeclarationList( theVarDeclarationList ), statementList( theStatementList ), expression( theExpression )
{
}

AbstractTreeGenerator::CMethodDeclaration::~CMethodDeclaration()
{
}

void AbstractTreeGenerator::CMethodDeclaration::Accept( IVisitor * v )
{
	v->visit( this );
}
const std::shared_ptr<AbstractTreeGenerator::CType> AbstractTreeGenerator::CMethodDeclaration::GetType() const
{
	return type;
}

const std::shared_ptr<AbstractTreeGenerator::CIdExpression> AbstractTreeGenerator::CMethodDeclaration::GetIdExpression() const
{
	return idExpression;
}

const std::shared_ptr<AbstractTreeGenerator::CArgumentList> AbstractTreeGenerator::CMethodDeclaration::GetArgumentList() const
{
	return argumentList;
}

const std::shared_ptr<AbstractTreeGenerator::CVarDeclarationList> AbstractTreeGenerator::CMethodDeclaration::GetVarDeclarationList() const
{
	return varDeclarationList;
}

const std::shared_ptr<AbstractTreeGenerator::CStatementList> AbstractTreeGenerator::CMethodDeclaration::GetStatementList() const
{
	return statementList;
}

const std::shared_ptr<AbstractTreeGenerator::IExpression> AbstractTreeGenerator::CMethodDeclaration::GetExpression() const
{
	return expression;
}

