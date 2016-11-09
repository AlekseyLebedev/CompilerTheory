#pragma once

#include <string>
#include <unordered_map>
#include "Symbol.h"
#include "Info.h"

// таблица символов
class CTable {
public:
	void insert( const CSymbol& theSymbol, const IInfo& theInfo);
	void pop(const std::string& theName );
	// для избежания коллизий при удалении нужно передавать информацию об объекте
	void pop(const std::string& theName, const IInfo& theInfo );
	// метод для поиска переменной в таблице (включая все предыдущие секции)
	const IInfo lookup(const CSymbol& theSymbol ) const;

private:
	// не уверен что должно быть именно так
	std::unordered_map < CSymbol, IInfo > table;
};