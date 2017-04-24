#pragma once
#include <vector>
#include <memory>

#include "..\IRTree\IRTTemp.h"
#include "..\IRTree\IRTLabel.h"

#include "OperationType.h"

namespace CodeGeneration {

	template <typename T>
	class CSharedPtrVector : public std::vector<std::shared_ptr<T> > {

	};

	using CTemp = IRTree::Temp;
	using CLabel = IRTree::Label;

	// Базовый класс инструкции
	class IInstruction {
	public:
		virtual ~IInstruction() {};
		// Превращает в строку кода на ассемблере
		virtual std::wstring ToCode() = 0; // TODO потом добавиться маппинг Temp в регистры и переменные на стеке
	};

	// Определение точки перехода
	class CLabelDefinition : public IInstruction {
	public:
		CLabelDefinition( std::shared_ptr<CLabel>& theLabel ) : label( theLabel ) {}
		std::shared_ptr<CLabel> GetLabel();
		virtual std::wstring ToCode() override;

	private:
		std::shared_ptr<CLabel> label;

	};

	// Ассемблерная инструкция
	class COperation : public IInstruction {
	public:
		COperation( TOperationType code ) : instructionCode( code )
		{
		}

		TOperationType GetInstructionCode();
		CSharedPtrVector<CTemp>& GetArguments();
		CSharedPtrVector<CTemp>& GetDefinedTemps();
		CSharedPtrVector<CLabel>& GetJumpPoints();
		std::vector<int>& GetConstants();
		virtual std::wstring ToCode() override;

	private:
		TOperationType instructionCode;
		CSharedPtrVector<CTemp> arguments;
		CSharedPtrVector<CTemp> definedTemps;
		CSharedPtrVector<CLabel> jumpPoints;
		std::vector<int> constants;
	};

	// Операция перемещения данных. Отдельно, т.к. полезна для алгоритма распредления темпов по регистрам и стеку
	class CMoveOperation : public COperation {
	public:
		CMoveOperation( std::shared_ptr<CTemp>& from, std::shared_ptr<CTemp>& to ) : COperation( OT_Move )
		{
			GetArguments().push_back( to );
			GetArguments().push_back( from );
		}

		std::shared_ptr<CTemp> GetFrom();
		std::shared_ptr<CTemp> GetTo();
	};

	// Операция вызова функции. Отдельно - т.к. сложная платформозависимая логика расопложения
	// аргументов (ABI: __stdcall, __fastcall, cdecl и т.д.) и необходимо сохранять значение регистров (TODO)
	class CCallOperation : public COperation {
	public:
		CCallOperation( const std::shared_ptr<CLabel>& label ) : COperation( OT_Call )
		{
			GetJumpPoints().push_back( label );
		}

		virtual std::wstring ToCode();
	};

} // namespace CodeGeneration
