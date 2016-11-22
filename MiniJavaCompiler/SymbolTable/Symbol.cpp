#include "Symbol.h"

namespace SymbolTable {
	CSymbol::CSymbol( const std::string & theSymbol )
	{

	}

	const std::string & CSymbol::String() const
	{
		return symbol;
	}

	const int CSymbol::Num() const
	{
		return num;
	}

}