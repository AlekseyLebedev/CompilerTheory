#include "IRTSExp.h"

IRTree::IRTSExp::IRTSExp( const IRTExression* _exp ) : exp( _exp )
{
}

const IRTree::IRTExpression* IRTree::IRTSExp::GetExp() const
{
	return exp;
}

void IRTree::IRTSExp::Accept( IIRTreeVisitor *visitor ) const
{
	visitor->Visit( this );
}

const IRTree::IRTExpList* IRTree::IRTSExp::children() const
{
	//TO DO
	return nullptr;
}
