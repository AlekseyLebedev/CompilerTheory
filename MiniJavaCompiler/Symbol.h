#pragma once

#include <string>
#include <unordered_map>

class CSymbol {
public:
	CSymbol( const std::string& theSymbol );
	const std::string& String() const;

	CSymbol( const CSymbol& ) = delete;
	void operator=( const CSymbol& ) = delete;
private:
	std::string symbol;
};

//template<>
//class cmpCSymbol<CSymbol> {
//public:
//	bool operator() {
//		
//	}
//};


// TODO: разобраться почему ошибки линковки
// механизм интернирования - из лекции, кажется для быстрого сравнения
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
