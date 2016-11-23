#pragma once
#include "VariableInfo.h"
#include <vector>

namespace SymbolTable {

	// TODO: ������ ����� ������ ���� �������� � ����� ����������, ��������� ���������� � ������������� ��������

	// ���������� � �������
	class CMethodInfo {
	public:
		int GetReturnType();
		const CVariableInfo& GetVarInfo( const int& id );
		std::vector<int> GetArguments();
	};
}