#include <string>
#include <cassert>
#include <iostream>
#include <fstream>

#include "Printer.h"

namespace CodeGeneration
{
	CAssemlerCodePrinter::CAssemlerCodePrinter( const std::wstring& filename ) : output( filename + L".txt" )
	{
	}

	CAssemlerCodePrinter::~CAssemlerCodePrinter()
	{
		assert( !output.is_open() );
	}

	void CAssemlerCodePrinter::PrintBlock( CSharedPtrVector<IInstruction>& code )
	{
		for( size_t i = 0; i < code.size(); i++ ) {
			output << code[i]->ToCode() << std::endl;
		}
	}

	void CAssemlerCodePrinter::Close()
	{
		output.close();
	}

} // namespace CodeGeneration