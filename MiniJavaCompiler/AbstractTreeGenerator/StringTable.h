// Таблица строк для таблицы символов
// каждой строке будет соответствовать натуральный номер
// и при сравнении будет очень быстро сравниваться по номеру
#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace AbstractTreeGenerator {

	class CStringTable {
	public:
		// возвращает номер присвоенный новой строке, 0 - в случае повтора
		int insert( const std::string& theString );
		//// возвращает номер присвоенный ранее строке, 0 - в случае отсутствия строки
		//int find( const std::string& theString );

		// проверка совпадают ли две строки
		bool equals( const std::string& left, const std::string& right );

		// GetString( по номеру );
	private:
		// для сравнения будем использовать указатель на соответствующий символ
		// Для класса Symbol известно, что для каждой возможной строки есть один и только один объект Symbol.
		// Мы каждой строке сопоставим число
		std::unordered_map< std::string, int > stringTable;
	};

}