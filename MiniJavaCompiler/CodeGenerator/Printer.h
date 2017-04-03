#pragma once

#include "Instruction.h"

namespace CodeGeneration
{

	class CAssemlerCodePrinter {
	public:
		CAssemlerCodePrinter( const std::wstring& filename );
		~CAssemlerCodePrinter();

		void PrintBlock( CSharedPtrVector<IInstruction>& code );

		void Close();

	private:
		std::wofstream output;
	};
} // namespace CodeGeneration
