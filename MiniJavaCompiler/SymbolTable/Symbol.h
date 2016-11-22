#pragma once

#include <string>
namespace SymbolTable {

	// ���������� �������
	class CSymbol {
	public:
		CSymbol( const std::string& theSymbol );
		const std::string& String() const;
		const int Num() const;
		bool isEqual( const CSymbol& theSymbol ) const;

		CSymbol( const CSymbol& ) = delete;
		void operator=( const CSymbol& ) = delete;
	private:
		// TODO: ������ ������
		std::string symbol;
		// ����� � StringTable
		int num;
	};
}