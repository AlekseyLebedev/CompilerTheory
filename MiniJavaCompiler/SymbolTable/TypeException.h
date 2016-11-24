#pragma once
#include <string>
#include <sstream>


namespace SymbolTable {
	class CTypeException : public std::exception {
	public:
		virtual char const* what() const override;
		CTypeException( int col, int row, const std::string& msg );
	private:
		std::stringstream message;
		std::string msgresult;
	};
}