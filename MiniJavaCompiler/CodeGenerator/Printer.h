#pragma once

#include "Instruction.h"

namespace CodeGeneration
{

	void PrintToFile( CSharedPtrVector<IInstruction>& code, const std::wstring& filename );

} // namespace CodeGeneration
