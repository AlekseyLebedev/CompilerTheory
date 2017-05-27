#pragma once

#include <memory>
#include <map>
#include <list>
#include "Instruction.h"

#include "..\IRTree\Frame.h"
#include "..\IRTree\IRTStatement.h"

namespace CodeGeneration
{
	class CAssemlerCodePrinter {
	public:
		CAssemlerCodePrinter( const std::wstring& filename );
		~CAssemlerCodePrinter();

		void PrintBlock( CSharedPtrVector<IInstruction>& code, std::map<int, int>& colors );

		void Close();

	private:
		std::wofstream output;
	};

	class CAssemblerCodeCreator {
	public:
		CAssemblerCodeCreator( std::list<std::pair<std::shared_ptr<IRTree::IRTStatement>, std::shared_ptr<IRTree::CFrame>>>& basisBlocks, std::wstring& filename );
		void AllocateRegistersAndPrint();


	private:
		CodeGeneration::CAssemlerCodePrinter assemblePrinter;
		std::vector<CSharedPtrVector<IInstruction>> commands;
		CSharedPtrVector<IRTree::CFrame> frames;

		void addTempToStack( int blockIndex, std::shared_ptr<CTemp>& problemTemp );
	};
} // namespace CodeGeneration
