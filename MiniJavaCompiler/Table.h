#pragma once

#include <string>
#include <map>
#include <list>
#include "Symbol.h"
#include "Info.h"

typedef std::map< CSymbol, IInfo > block;

// таблица символов
class CTable {
public:
	// добавляет новый блок в таблицу
	void addBlock();
	// удаляет текущий блок
	void deleteBlock();
	// удаялет указанный блок
	void deleteBlock( block* theBlock );

	void insertSymbol( const CSymbol& theSymbol, const IInfo& theInfo );
	void popSymbol( const std::string& theName );
	// для избежания коллизий при удалении нужно передавать информацию об объекте
	void popSymbol( const std::string& theName, const IInfo& theInfo );

	// TODO: возвращать итератор
	// метод для поиска переменной в таблице (включая все предыдущие секции)
	const IInfo lookup( const CSymbol& theSymbol ) const;
	// метод для поиска переменной в таблице по названию(включая все предыдущие секции)
	const IInfo lookup( const std::string& theSymbolName ) const;

private:
	//Вариант реализации : список блоков
	//При входе во вложенную область – создаем новый блок и помещаем переменные в него
	//При выходе из области – удаляем последний блок
	std::list< block > table;

	// указатель на текущий блок
	block* currentBlock;
};