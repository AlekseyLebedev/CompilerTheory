#pragma once
#include "VariableInfo.h"
#include <vector>

namespace SymbolTable {

	// TODO: Каждый метод должен быть привязан к своим параметрам, локальным переменным и возвращаемому значению

	// информация о методах
	class CMethodInfo {
	public:
		int GetReturnType();
		const CVariableInfo& GetVarInfo( const int& id );
		std::vector<int> GetArguments();
	};
}