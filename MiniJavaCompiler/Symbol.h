#pragma once

#include <string>

class CSymbol {
public:
	const std::string& String() const;

	CSymbol( const CSymbol& ) = delete;
	void operator=( const CSymbol& ) = delete;
};
