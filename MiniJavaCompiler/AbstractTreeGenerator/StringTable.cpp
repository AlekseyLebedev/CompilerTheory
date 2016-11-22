#include "StringTable.h"

namespace AbstractTreeGenerator {
	int CStringTable::insert( const std::string& theString )
	{
		auto iter = stringTable.find( theString );
		// если строка уже встречалась, то возвращаем ее номер
		if( iter != stringTable.end() ) {
			return iter->second;
		}
		// если нет, то присваеваем новый номер
		// количство кэшированных строк
		int n = stringTable.size();
		// новой строке присваевается текущий номер
		stringTable.insert( std::make_pair( theString, n ) );
		return n;
	}

	//int CStringTable::find( const std::string& theString )
	//{
	//	auto iter = stringTable.find( theString );
	//	if( iter != stringTable.end() ) {
	//		return iter->second;
	//	}
	//	// в случае если не нашли
	//	return 0;
	//}

	bool CStringTable::equals( const std::string& left, const std::string& right )
	{
		int leftNum = insert( left );
		int rightNum = insert( right );
		// TODO: было бы неплохо тут проверить то, что обе строки вообще были в таблице
		// т.е. что find вернул не ноль
		return (leftNum == rightNum);
	}

}