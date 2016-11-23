#pragma once
#include "VariableInfo.h"
#include <vector>

namespace SymbolTable {

	// TODO: ������ ����� ������ ���� �������� � ����� ����������, ��������� ���������� � ������������� ��������

	// ���������� � �������
	class CMethodInfo {
	public:
		CVariableInfo GetVarInfo( const int& id );
		std::vector<int> GetArguments();
	};
}