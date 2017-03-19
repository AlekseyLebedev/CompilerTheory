#include "Generator.h"

void CGenerator::SetRoot( std::shared_ptr<IRTree::CCodeFragment>  theRoot )
{
	root = theRoot;
}

std::shared_ptr<IRTree::CCodeFragment>  CGenerator::GetRoot()
{
	return root;
}
