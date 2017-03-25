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

	int COperation::GetInstructionCode()
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
		// TODO
		return std::wstring();
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
