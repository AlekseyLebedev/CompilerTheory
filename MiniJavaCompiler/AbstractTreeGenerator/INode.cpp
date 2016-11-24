#include "INode.h"

int AbstractTreeGenerator::INode::GetCol()
{
	return startCol;
}

int AbstractTreeGenerator::INode::GetRow()
{
	return startRow;
}

extern int col;
extern int row;

AbstractTreeGenerator::INode::INode() :
	startCol( col ), startRow( row )
{
}
