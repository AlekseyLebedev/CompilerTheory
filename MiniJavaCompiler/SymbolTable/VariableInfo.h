#pragma once

namespace SymbolTable {

	// ���������� � ����������
	class CVariableInfo {
	public:
		int GetType();
		CVariableInfo();
		CVariableInfo( int );

	private:
		int type;
	};
}