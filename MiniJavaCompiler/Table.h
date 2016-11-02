#pragma once

#include <string>
#include <unordered_map>

#include "VariableInfo.h"

// таблица символов
class CTable {
public:
	void insert( std::string theName, CVariableInfo theVarInfo); // в книге void, но лучше сделать булевый результат
	void pop( std::string theName );
	// метод для поиска переменной в таблице (включая все предыдущие секции)
	CVariableInfo lookup( std::string theName );

private:
	// не уверен что должно быть именно так
	std::unordered_map < std::string, CVariableInfo > table;
};