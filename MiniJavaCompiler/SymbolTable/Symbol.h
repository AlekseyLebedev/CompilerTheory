#pragma once

#include <string>
namespace SymbolTable {

	// глобальная таблица
	class CSymbol {
	public:
		CSymbol( const std::string& theSymbol );
		const std::string& String() const;
		const int Num() const;
		bool isEqual( const CSymbol& theSymbol ) const;

		CSymbol( const CSymbol& ) = delete;
		void operator=( const CSymbol& ) = delete;
	private:
		// TODO: убрать строки
		std::string symbol;
		// номер в StringTable
		int num;
	};
}