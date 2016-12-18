#pragma once

namespace SymbolTable {

	// информация о переменной
	class CVariableInfo {
	public:
		int GetType() const;
		CVariableInfo();
		CVariableInfo( int );

	private:
		int type;
	};
}