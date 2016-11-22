// ��� ���� ����� ��� ������ ������� �� ��� ����������� 
// ������ ����� ��������� TypeChecker-�� � ��������� ������ ������
// ��� ����� ��� ������� ������ �� ������:
//     ������ ��� ������� � ����������� � ��� - ��� �� ������ � ���������
//	       ���������� ���������� � ������������ ����, ���� ���������� � �������
//     ������ ����� ������ � ����������� � ���

#pragma once

#include <string>
#include <map>
#include "Symbol.h"
#include "ClassInfo.h"
#include "MethodInfo.h"
#include "VariableInfo.h"
#include "..\AbstractTreeGenerator\StringTable.h"

namespace SymbolTable {

	// ������� ��������
	class CTable {
	public:

	private:
		// ����������� �� ����� � ������
		AbstractTreeGenerator::CStringTable stringTable;
		// ����������� �� ������� � ���������� � ���
		std::map<CSymbol, CClassInfo> classes;
	
	};
}