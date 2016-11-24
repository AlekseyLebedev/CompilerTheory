#include "INode.h"

int AbstractTreeGenerator::INode::GetCol() const
{
	return startCol;
}

int AbstractTreeGenerator::INode::GetRow() const
{
	return startRow;
}

extern int col;
extern int row;

AbstractTreeGenerator::INode::INode() :
	startCol( col ), startRow( row )
{
}
