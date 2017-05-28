#include <sstream>
#include <cassert>

#include "Instruction.h"

namespace CodeGeneration {

	std::shared_ptr<CLabel> CLabelDefinition::GetLabel()
	{
		return label;
	}

	std::wstring CLabelDefinition::ToCode( std::map<int, int>& )
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

	TOperationType COperation::GetType() const
	{
		return instructionCode;
	}

	static const wchar_t* registerPrefix = L"r";

	std::wstring COperation::ToCode( std::map<int, int>& colors )
	{
		std::wstring codeTemplate = GetOperationString( instructionCode );
		std::wstringstream result;
		int tempIndex = 0;
		int constIndex = 0;
		int jumpIndex = 0;
		for( size_t i = 0; i < codeTemplate.length(); i++ ) {
			switch( codeTemplate[i] ) {
				case L'\'':
				{
					int regNum = arguments[tempIndex++]->GetName();
					auto iterator = colors.find( regNum );
					if( iterator != colors.end() ) {
						result << RegisterName( iterator->second );
					} else {
						result << registerPrefix << regNum;
					}
					break;
				}
				case L'!':
					result << constants[constIndex++];
					break;
				case L'^':
					result << L"" << jumpPoints[jumpIndex++]->GetAssmeblerName();
					break;
				case L'+':
					result << (constants[constIndex] >= 0 ? "+" : "");
					break;
				default:
					result << codeTemplate[i];
					break;
			}
		}
		assert( constIndex == constants.size() );
		assert( jumpIndex == jumpPoints.size() );
		assert( tempIndex == arguments.size() || instructionCode == OT_Call );
		return result.str();
	}

	std::wstring COperation::RegisterName( int registerIndex )
	{
		switch( registerIndex ) {
			case 0:
				return L"%eax";
			case 1:
				return L"%ebx";
			case 2:
				return L"%ecx";
			case 3:
				return L"%edx";
			case 4:
				return L"%eex";

			default:
				assert( false );
				return L"Internal Program Error";
		}
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

	std::wstring CCallOperation::ToCode( std::map<int, int>& colors )
	{
		std::wstringstream result;

		// первый аргумент зарезервирован под возвращаемое значение
		assert( GetArguments().size() == 1 );
		result << COperation::ToCode( colors );
		assert( colors[GetArguments()[0]->GetName()] == 0 );

		return result.str();
	}

} // namespace CodeGeneration
