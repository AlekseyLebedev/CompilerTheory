#pragma once
#include <vector>
#include <memory>

#include "..\IRTree\IRTTemp.h"
#include "..\IRTree\IRTLabel.h"

#include "OperationType.h"

template <typename T>
class CSharedPtrVector : public std::vector<std::shared_ptr<T> > {

};

namespace CodeGeneration {
	using CTemp = IRTree::Temp;
	using CLabel = IRTree::Label;

	class IInstruction {
	public:
		virtual ~IInstruction() {};
		// Превращает в строку кода на ассемблере
		virtual std::wstring ToCode() = 0; // TODO потом добавиться маппинг Temp в регистры и переменные на стеке
	};

	class CLabelDefinition : public IInstruction {
	public:
		std::shared_ptr<CLabel> GetLabel();
		virtual std::wstring ToCode() override;

	private:
		std::shared_ptr<CLabel> label;

	};

	class COperation : public IInstruction {
	public:
		COperation( int code ) : instructionCode( code )
		{
		}

		int GetInstructionCode();
		CSharedPtrVector<CTemp>& GetArguments();
		CSharedPtrVector<CTemp>& GetDefinedTemps();
		CSharedPtrVector<CLabel>& GetDefinedJumpPoint();
		std::vector<int>& GetConstants();
		virtual std::wstring ToCode() override;

	private:
		int instructionCode;
		CSharedPtrVector<CTemp> arguments;
		CSharedPtrVector<CTemp> definedTemps;
		CSharedPtrVector<CLabel> jumpPoints;
		std::vector<int> constants;
	};

	class CMoveOperation : public COperation {
	public:
		CMoveOperation( std::shared_ptr<CTemp>& from, std::shared_ptr<CTemp>& to ) : COperation( OT_Move )
		{
			GetArguments().push_back( from );
			GetArguments().push_back( to );
		}

		std::shared_ptr<CTemp> GetFrom();
		std::shared_ptr<CTemp> GetTo();
	};

} // namespace CodeGeneration
