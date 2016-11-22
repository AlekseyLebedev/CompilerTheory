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
		v.push_back( theString );
		return n;
	}

	std::string CStringTable::find( const int num )
	{
		if( num < v.size() ) {
			return v[num];
		}
		return std::string("Error in std::string CStringTable::find( const int num )! \n ");
	}

	bool CStringTable::equals( const std::string& left, const std::string& right )
	{
		int leftNum = insert( left );
		int rightNum = insert( right );
		return (leftNum == rightNum);
	}

}