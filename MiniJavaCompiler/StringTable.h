// ������� ����� ��� ������� ��������
// ������ ������ ����� ��������������� ����������� �����
// � ��� ��������� ����� ����� ������ ������������ �� ������
#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Symbol.h"


class CStringTable {
public:
	bool insert( std::string& theString, CSymbol* theSymbol );

private:
	// ��� ��������� ����� ������������ ��������� �� ��������������� ������
	// ��� ������ Symbol ��������, ��� ��� ������ ��������� ������ ���� ���� � ������ ���� ������ Symbol.
	// �.�.��������� ����� ����� ������ � ��������� ����������
	std::unordered_map< std::string, CSymbol* > stringTable;

	// ��� ������� ������� ��� ����� - ����� map
	std::vector<std::string> v;
};
