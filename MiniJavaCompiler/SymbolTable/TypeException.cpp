#include "TypeException.h"

namespace SymbolTable {

	char const * CTypeException::what() const
	{
		return msgresult.c_str();
	}

	CTypeException::CTypeException( int col, int row, const std::string & msg )
	{
		message = std::stringstream();
		message << "Col: " << col << " row: " << row << " Error: " << msg;
		msgresult = message.str();
	}
}
