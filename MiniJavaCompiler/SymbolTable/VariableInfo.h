#pragma once

namespace SymbolTable {

	// ���������� � ����������
	class CVariableInfo {
	public:
		int GetType() const;
		CVariableInfo();
		CVariableInfo( int );

	private:
		int type;
	};
}