#pragma once

#include <string>
#include <unordered_map>

#include "VariableInfo.h"

// ������� ��������
class CTable {
public:
	void insert( std::string theName, CVariableInfo theVarInfo); // � ����� void, �� ����� ������� ������� ���������
	void pop( std::string theName );
	// ����� ��� ������ ���������� � ������� (������� ��� ���������� ������)
	CVariableInfo lookup( std::string theName );

private:
	// �� ������ ��� ������ ���� ������ ���
	std::unordered_map < std::string, CVariableInfo > table;
};