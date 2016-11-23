// крч план такой при первом проходе мы все интернируем 
// второй обход совершаем TypeChecker-ом и проверяем всякие ошибки
// для этого для каждого класса мы храним:
//     список его методов с информацией о них - мап из метода в методинфо
//	       содержащий информацию о возвращаемом типе, типе аргументов и прочего
//     список полей класса с информацией о них
#pragma once

#include <string>
#include <map>
#include <utility>
#include "Symbol.h"
#include "ClassInfo.h"
#include "MethodInfo.h"
#include "VariableInfo.h"
#include "..\AbstractTreeGenerator\StringTable.h"

namespace SymbolTable {

	// таблица символов
	class CTable {
	public:
		// добавить новый класс в таблицу символов
		void AddClass( const CSymbol& theSymbol, const CClassInfo& theClassInfo );
		const CClassInfo GetClassInfo( const CSymbol& theSymbol ) const;
		CClassInfo GetClassInfo( const int& id );
		int GetClass( const int& id );
	private:
		// отображение из строк в номера
		AbstractTreeGenerator::CStringTable stringTable;

		// отображение из классов в информацию о них
		std::vector<CSymbol> classes;
		std::vector<CClassInfo> classesInfo;
	
	};
}