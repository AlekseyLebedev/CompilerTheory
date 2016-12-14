#include "IRTSExp.h"

IRTree::IRTSExp::IRTSExp( const IRTExpression* _exp ) : exp( _exp )
{
}

const IRTree::IRTExpression* IRTree::IRTSExp::GetExp() const
{
	return exp;
}

void IRTree::IRTSExp::Accept( IRTreeVisitor* visitor ) const
{
	visitor->Visit( this );
}

const IRTree::IRTExpList* IRTree::IRTSExp::children() const
{
	//TO DO
	return nullptr;
}
