#include "TypeException.h"

namespace SymbolTable {

	char const * CTypeException::what() const
	{
		return message.str().c_str();
	}

	CTypeException::CTypeException( int col, int row, std::string msg )
	{
		message << "Col: " << col << " row: " << row << " Error: " << msg;
	}
}
