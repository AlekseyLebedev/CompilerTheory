#include "BOOL_LITERAL.h"
#include <cassert>

AbstractTreeGenerator::CBOOL_LITERAL::CBOOL_LITERAL(std::string theValue) 
{
	// �������� ������������, �.�. �� ��� ���� �������� �������� ������ �������� ����
	assert(theValue == "TRUE" || theValue == "FALSE" || theValue == "true" || theValue == "false");
	if (theValue == "TRUE" || theValue == "true") {
		value = true;
	} else {
		value = false;
	}
}

AbstractTreeGenerator::CBOOL_LITERAL::CBOOL_LITERAL(bool theValue) : value(theValue)
{

}

AbstractTreeGenerator::CBOOL_LITERAL::~CBOOL_LITERAL()
{

}