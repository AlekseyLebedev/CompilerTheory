#include "Table.h"
#include "assert.h"

void CTable::addBlock()
{
	
}

void CTable::deleteBlock()
{
	// �������� �� �� ��� � ������� ��� ���� �����
	assert( table.empty() );
}

void CTable::deleteBlock( block * theBlock )
{
}

void CTable::insertSymbol( const CSymbol & theSymbol, const IInfo & theInfo )
{
	
}

void CTable::popSymbol( const std::string & theName )
{
}

void CTable::popSymbol( const std::string & theName, const IInfo & theInfo )
{
}

const IInfo CTable::lookup( const CSymbol & theSymbol ) const
{
	return IInfo();
}

const IInfo CTable::lookup( const std::string & theSymbolName ) const
{
	return IInfo();
}
