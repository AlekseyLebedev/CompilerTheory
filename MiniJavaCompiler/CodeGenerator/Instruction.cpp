#include <sstream>
#include <cassert>

#include "Instruction.h"

namespace CodeGeneration {

	std::shared_ptr<CLabel> CLabelDefinition::GetLabel()
	{
		return label;
	}

	std::wstring CLabelDefinition::ToCode()
	{
		return label->GetAssmeblerName() + L":";
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

	static const wchar_t* registerPrefix = L"r";

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
					result << registerPrefix << arguments[tempIndex++]->GetName();
					break;
				case L'!':
					result << constants[constIndex++];
					break;
				case L'^':
					result << L"" << jumpPoints[jumpIndex++]->GetAssmeblerName();
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
		return GetArguments()[1];
	}

	std::shared_ptr<CTemp> CMoveOperation::GetTo()
	{
		return GetArguments()[0];
	}

	//-----------------------------------------------------------------------------------------------------------------

	std::wstring CCallOperation::ToCode()
	{
		std::wstringstream result;
		result << L"; begin call" << std::endl;
		// TODO сохранение регистров!!!

		// первый аргумент зарезервирован под возвращаемое значение
		assert( GetArguments().size() > 0 );
		for( size_t i = 1; i < GetArguments().size(); i++ ) {
			// —корее всего будем делать так, по cdecl
			result << "PUSH " << registerPrefix << GetArguments()[i]->GetName() << std::endl;
		}
		result << COperation::ToCode() << std::endl;
		// ј вот это не по cdecl. “ип вызвающа€ функци€ чистит только аргументы
		// TODO: либо переделать по cdecl с учетом текущей щан€тости стека, либо придумать как делаем
		result << L"; TODO: rewrite after temps moved to registers and stack" << std::endl;
		//result << "ADD %esp " << ((GetArguments().size() - 1) * sizeof( int )) << std::endl;
		// ¬озвращаемое значение тоже по cdecl
		result << "MOV " << registerPrefix << GetArguments()[0]->GetName() << L" %eax";
		result << L"; end call" << std::endl;

		return result.str();
	}

} // namespace CodeGeneration
