#pragma once

namespace SymbolTable {

	// TODO: Все переменные и параметры функций должны быть привязаны к своим типам

	// информация о переменной
	class CVariableInfo {
	public:
		std::shared_ptr<AbstractTreeGenerator::IType> GetType();
	};
}