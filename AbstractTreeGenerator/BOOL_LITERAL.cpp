#include "BOOL_LITERAL.h"
#include <cassert>

FirstTask::CBOOL_LITERAL::CBOOL_LITERAL(std::string theValue) 
{
	// �������� ������������, �.�. �� ��� ���� �������� �������� ������ �������� ����
	assert(theValue == "TRUE" || theValue == "FALSE" || theValue == "true" || theValue == "false");
	if (theValue == "TRUE" || theValue == "true") {
		value = true;
	} else {
		value = false;
	}
}

FirstTask::CBOOL_LITERAL::CBOOL_LITERAL(bool theValue) : value(theValue)
{

}

FirstTask::CBOOL_LITERAL::~CBOOL_LITERAL()
{

}