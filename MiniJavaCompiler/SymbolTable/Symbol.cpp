#include "Symbol.h"

namespace SymbolTable {
	CSymbol::CSymbol( const std::string & theSymbol )
	{

	}

	const std::string & CSymbol::String() const
	{
		// TODO: �������� ������ �� �������� num �� StringTable - ����� ������� ���������� ��������
		return symbol;
	}

	const int CSymbol::Num() const
	{
		return num;
	}

	bool CSymbol::isEqual( const CSymbol & theSymbol ) const
	{
		return (Num() == theSymbol.Num());
	}

}