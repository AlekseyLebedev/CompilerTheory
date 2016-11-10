#pragma once

#include <string>
//#include <unordered_map>
#include <map>
#include <list>
#include "Symbol.h"

// таблица символов
class CTable {
public:
	//  нужно делать иначе
	//// добавляет новый блок в таблицу
	//void addBlock();
	//// удаляет последний блок, может потеряться валидность итератора на текущий блок
	//void deleteBlock();
	//// удаялет указанный блок, нет проверки валидности блока
	//void deleteBlock( std::list< block* >::iterator theBlockIter );

	//void insertSymbol( const CSymbol& theSymbol, const IInfo& theInfo );
	//// удаляет символ по имени
	//void popSymbol( const std::string& theName );
	//// при удалении нужно передавать информацию об объекте
	//void popSymbol( const std::string& theName, const IInfo& theInfo );
	//// получить итератор на текущий блок
	//std::list< block* >::iterator getCurrentBlockIter();
	//
	//// метод для поиска переменной в таблице (включая все предыдущие секции)
	//std::pair< block::iterator, bool > find( const CSymbol& theSymbol );
	//// метод для поиска переменной в таблице по названию(включая все предыдущие секции)
	//std::pair< block::iterator, bool > find( const std::string& theSymbolName );

private:
	////Вариант реализации : список блоков
	////При входе во вложенную область – создаем новый блок и помещаем переменные в него
	////При выходе из области – удаляем последний блок
	//std::list< block* > table;

	////// указатель на текущий блок
	////block* currentBlock;
	//// итератор на текущий блок
	//std::list< block* >::iterator currentBlockIter;
};