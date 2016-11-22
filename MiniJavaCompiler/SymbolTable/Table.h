#pragma once

#include <string>
#include <vector>
#include "Symbol.h"
#include "ClassInfo.h"
#include "MethodInfo.h"
#include "VariableInfo.h"
#include "..\AbstractTreeGenerator\StringTable.h"

namespace SymbolTable {

	// таблица символов
	class CTable {
	public:
		// отображение из строк в номера
		AbstractTreeGenerator::CStringTable stringTable;
		// отображение из номеров в CSymbol
		std::vector<CSymbol> v;
		// хранить мап дл€ всего


		////  нужно делать иначе
		//// добавл€ет новый блок в таблицу
		//void addBlock();
		//// удал€ет последний блок, может потер€тьс€ валидность итератора на текущий блок
		//void deleteBlock();
		//// уда€лет указанный блок, нет проверки валидности блока
		//void deleteBlock( std::list< block* >::iterator theBlockIter );

		//void insertSymbol( const CSymbol& theSymbol, const IInfo& theInfo );
		//// удал€ет символ по имени
		//void popSymbol( const std::string& theName );
		//// при удалении нужно передавать информацию об объекте
		//void popSymbol( const std::string& theName, const IInfo& theInfo );
		//// получить итератор на текущий блок
		//std::list< block* >::iterator getCurrentBlockIter();
		//
		//// метод дл€ поиска переменной в таблице (включа€ все предыдущие секции)
		//std::pair< block::iterator, bool > find( const CSymbol& theSymbol );
		//// метод дл€ поиска переменной в таблице по названию(включа€ все предыдущие секции)
		//std::pair< block::iterator, bool > find( const std::string& theSymbolName );

	private:
		////¬ариант реализации : список блоков
		////ѕри входе во вложенную область Ц создаем новый блок и помещаем переменные в него
		////ѕри выходе из области Ц удал€ем последний блок
		//std::list< block* > table;

		////// указатель на текущий блок
		////block* currentBlock;
		//// итератор на текущий блок
		//std::list< block* >::iterator currentBlockIter;
	};
}