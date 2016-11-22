#include "Table.h"

namespace SymbolTable {
	void CTable::AddClass( const CSymbol& theSymbol, const CClassInfo& theClassInfo )
	{
		// TODO: стоит изменить способ хранения классов и информации но пока и так сойдет
		classes.push_back( theSymbol );
		classesInfo.push_back( theClassInfo );
	}
	const CClassInfo CTable::GetClassInfo( const CSymbol & theSymbol ) const
	{
		int size = classes.size();
		for( int i = 0; i < size; ++i ) {
			if( classes[i].isEqual( theSymbol ) ) {
				return classesInfo[i];
			}
		}
		// TODO: наверное стоит в случае неудачи как-то сигнализировать об ошибке
	}
}