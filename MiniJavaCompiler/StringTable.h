// Таблица строк для таблицы символов
// каждой строке будет соответствовать натуральный номер
// и при сравнении будет очень быстро сравниваться по номеру
#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Symbol.h"


class CStringTable {
public:
	bool insert( std::string& theString, CSymbol* theSymbol );

private:
	// для сравнения будем использовать указатель на соответствующий символ
	// Для класса Symbol известно, что для каждой возможной строки есть один и только один объект Symbol.
	// Т.е.сравнение строк можно свести к сравнению указателей
	std::unordered_map< std::string, CSymbol* > stringTable;

	// так сказать вариант для лалок - нужно map
	std::vector<std::string> v;
};
