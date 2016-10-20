#include "ClassDeclaration.h"

AbstractTreeGenerator::CClassDeclaration::CClassDeclaration( CIdExpression* theIdExpression,
	CClassExtend* theClassExtend,
	CVarDeclarationList* theVarDeclarationList,
	CMethodDeclarationList* theMethodDeclarationList ) :
	idExpression( theIdExpression ), classExtend( theClassExtend ),
	varDeclarationList( theVarDeclarationList ), methodDeclarationList( theMethodDeclarationList )
{
}

AbstractTreeGenerator::CClassDeclaration::~CClassDeclaration()
{
}

void AbstractTreeGenerator::CClassDeclaration::Accept( IVisitor * v )
{
	v->visit( this );
}
const std::shared_ptr<AbstractTreeGenerator::CIdExpression> AbstractTreeGenerator::CClassDeclaration::GetIdExpression() const {
	 return idExpression;
}

const std::shared_ptr<AbstractTreeGenerator::CClassExtend> AbstractTreeGenerator::CClassDeclaration::GetClassExtend() const {
	 return classExtend;
}

const std::shared_ptr<AbstractTreeGenerator::CVarDeclarationList> AbstractTreeGenerator::CClassDeclaration::GetVarDeclarationList() const {
	 return varDeclarationList;
}

const std::shared_ptr<AbstractTreeGenerator::CMethodDeclarationList> AbstractTreeGenerator::CClassDeclaration::GetMethodDeclarationList() const {
	 return methodDeclarationList;
}

