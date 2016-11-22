// Таблица строк для таблицы символов
// каждой строке будет соответствовать натуральный номер
// и при сравнении будет очень быстро сравниваться по номеру
#pragma once
#include <string>
#include <vector>
#include <unordered_map>

namespace AbstractTreeGenerator {

	class CStringTable {
	public:
		// возвращает номер присвоенный новой строке
		int insert( const std::string& theString );
		// возвращает строку по номеру 
		std::string find( const int num);

		// проверка совпадают ли две строки
		bool equals( const std::string& left, const std::string& right );

	private:
		// для сравнения строк будем использовать уникальный номер
		// Для класса Symbol известно, что для каждой возможной строки есть один и только один объект Symbol.
		// Мы каждой строке сопоставим число
		// и будем хранить вектор для случая, если нам понадобится сама строка а не ее номер
		std::unordered_map< std::string, int > stringTable;
		std::vector<std::string> v;
	};

}