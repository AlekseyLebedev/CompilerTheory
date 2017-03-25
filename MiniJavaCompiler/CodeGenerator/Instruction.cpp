#include <sstream>

#include "Instruction.h"

namespace CodeGeneration {

	std::shared_ptr<CLabel> CLabelDefinition::GetLabel()
	{
		return label;
	}

	std::wstring CLabelDefinition::ToCode()
	{
		return label->GetAssmeblerName();
	}

	//-----------------------------------------------------------------------------------------------------------------

	TOperationType COperation::GetInstructionCode()
	{
		return instructionCode;
	}

	CSharedPtrVector<CTemp>& COperation::GetArguments()
	{
		return arguments;
	}

	CSharedPtrVector<CTemp>& COperation::GetDefinedTemps()
	{
		return definedTemps;
	}

	CSharedPtrVector<CLabel>& COperation::GetJumpPoints()
	{
		return jumpPoints;
	}

	std::vector<int>& COperation::GetConstants()
	{
		return constants;
	}

	std::wstring COperation::ToCode()
	{
		std::wstring codeTemplate = GetOperationString( instructionCode );
		std::wstringstream result;
		int tempIndex = 0;
		int constIndex = 0;
		int jumpIndex = 0;
		for( size_t i = 0; i < codeTemplate.length(); i++ ) {
			switch( codeTemplate[i] ) {
				case L'\'':
					result << L"r" << arguments[tempIndex++];
					break;
				case L'!':
					result << L"r" << constants[constIndex++];
					break;
				default:
					result << codeTemplate[i];
					break;
			}
		}
		return result.str();
	}

	//-----------------------------------------------------------------------------------------------------------------

	std::shared_ptr<CTemp> CMoveOperation::GetFrom()
	{
		return GetArguments()[0];
	}

	std::shared_ptr<CTemp> CMoveOperation::GetTo()
	{
		return GetArguments()[1];
	}

} // namespace CodeGeneration
