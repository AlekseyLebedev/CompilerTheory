#include "LengthExpression.h"

AbstractTreeGenerator::CLengthExpression::CLengthExpression( std::shared_ptr<IExpression> theExpression ) :
	expression( theExpression )
{
}

AbstractTreeGenerator::CLengthExpression::~CLengthExpression()
{
}

void AbstractTreeGenerator::CLengthExpression::Accept( IVisitor * v )
{
	v->visit( this );
}
