#include "MethodDeclaration.h"

AbstractTreeGenerator::CMethodDeclaration::CMethodDeclaration( std::shared_ptr<CType> theType,
	std::shared_ptr<CIdExpression> theIdExpression,
	std::shared_ptr<CArgumentList> theArgumentList,
	std::shared_ptr<CVarDeclarationList>  theVarDeclarationList,
	std::shared_ptr<CStatementList>  theStatementList,
	std::shared_ptr<IExpression> theExpression ) : 
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
