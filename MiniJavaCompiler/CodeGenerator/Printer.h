#pragma once

#include <memory>
#include <map>
#include <list>
#include "Instruction.h"

#include "..\IRTree\Frame.h"
#include "..\IRTree\IRTStatement.h"

namespace CodeGeneration
{
	void HandleBlocks( std::list<std::pair<std::shared_ptr<IRTree::IRTStatement>, std::shared_ptr<IRTree::CFrame>>>& basisBlocks, int& fileIndex );

	class CAssemlerCodePrinter {
	public:
		CAssemlerCodePrinter( const std::wstring& filename );
		~CAssemlerCodePrinter();

		void PrintBlock( CSharedPtrVector<IInstruction>& code, std::map<int, int>& colors );

		void Close();

	private:
		std::wofstream output;
	};
} // namespace CodeGeneration
