#pragma once

#include <string>
namespace SymbolTable {

	// ���������� �������
	class CSymbol {
	public:
		CSymbol( const std::string& theSymbol );
		const std::string& String() const;
		const int Num() const;

		CSymbol( const CSymbol& ) = delete;
		void operator=( const CSymbol& ) = delete;
	private:
		// TODO: ������ ������
		std::string symbol;
		// ����� � StringTable
		int num;
	};

	//template<>
	//class cmpCSymbol<CSymbol> {
	//public:
	//	bool operator() {
	//		
	//	}
	//};


	// TODO: ����������� ������ ������ ��������
	// �������� �������������� - �� ������, ������� ��� �������� ���������
	//CSymbol* getIntern( const std::string& src )
	//{
	//	static std::unordered_map<std::string, CSymbol*> allStrings;
	//	auto cached = allStrings.find( src );
	//	if( cached != allStrings.end() ) {
	//		return cached->second;
	//	}
	//	CSymbol* newVal = new CSymbol( src );
	//	allStrings.insert( { src, newVal } );
	//	return newVal;
	//}
}