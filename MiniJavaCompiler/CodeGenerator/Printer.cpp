#include <string>
#include <string>
#include <iostream>
#include <fstream>

#include "Printer.h"

namespace CodeGeneration
{

	void PrintToFile( CSharedPtrVector<IInstruction>& code, const std::wstring& filename )
	{
		std::wofstream output( filename + L".txt" );
		for( size_t i = 0; i < code.size(); i++ ) {
			output << code[i]->ToCode() << std::endl;
		}
		output.close();
	}

} // namespace CodeGeneration