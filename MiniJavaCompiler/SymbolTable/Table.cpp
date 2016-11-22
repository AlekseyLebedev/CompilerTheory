#include "Table.h"
#include "assert.h"

namespace SymbolTable {

	//void CTable::addBlock()
	//{
	//	block* newBlock = new block();
	//	currentBlockIter = table.insert( table.end(), newBlock );
	//}
	//
	//void CTable::deleteBlock()
	//{
	//	// проверка на то что в таблице еще есть блоки
	//	assert( table.empty() );
	//	table.pop_back();
	//}
	//
	//void CTable::deleteBlock( std::list< block* >::iterator theBlockIter )
	//{
	//	// проверка на то что в таблице еще есть блоки
	//	assert( table.empty() );
	//	table.erase( theBlockIter );
	//}
	//
	//void CTable::insertSymbol( const CSymbol & theSymbol, const IInfo & theInfo )
	//{
	//}
	//
	//void CTable::popSymbol( const std::string & theName )
	//{
	//}
	//
	//void CTable::popSymbol( const std::string & theName, const IInfo & theInfo )
	//{
	//}
	//
	//std::list< block* >::iterator CTable::getCurrentBlockIter()
	//{
	//	return currentBlockIter;
	//}
	//
	//std::pair< block::iterator, bool >  CTable::find( const CSymbol & theSymbol )
	//{
	//	std::list< block* >::iterator curBlockIt = getCurrentBlockIter();
	//	bool isFound = false;
	//
	//	while( (!isFound) && (curBlockIt != table.begin()) ) {
	//		block::iterator res = (*curBlockIt)->find( theSymbol );
	//		if( res != (*curBlockIt)->end() ) {
	//			isFound = true;
	//			return std::make_pair( res, isFound );
	//		}
	//	}
	//	return std::make_pair( block::iterator(), isFound );
	//}
	//
	//std::pair< block::iterator, bool >  CTable::find( const std::string & theSymbolName )
	//{
	//	std::list< block* >::iterator curBlockIt = getCurrentBlockIter();
	//	bool isFound = false;
	//	return std::make_pair( block::iterator(), isFound );
	//}
}