#pragma once

namespace SymbolTable {

	// информация о переменной
	class CVariableInfo {
	public:
		int GetType();
		CVariableInfo();
		CVariableInfo( int );

	private:
		int type;
	};
}