#pragma once

namespace SymbolTable {

	// ���������� � ����������
	class CVariableInfo {
	public:
		int GetType();

		CVariableInfo( int );

	private:
		int type;
	};
}