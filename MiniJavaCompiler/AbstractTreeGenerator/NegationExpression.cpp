#include "NegationExpression.h"

AbstractTreeGenerator::CNegationExpression::CNegationExpression( std::shared_ptr<IExpression> theExpression ) :
	expression( theExpression )
{
}

AbstractTreeGenerator::CNegationExpression::~CNegationExpression()
{
}

void AbstractTreeGenerator::CNegationExpression::Accept( IVisitor * v )
{
	v->visit( this );
}
