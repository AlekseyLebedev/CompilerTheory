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

	// ������� ����� ����������
	class IInstruction {
	public:
		virtual ~IInstruction() {};
		// ���������� � ������ ���� �� ����������
		virtual std::wstring ToCode() = 0; // TODO ����� ���������� ������� Temp � �������� � ���������� �� �����
	};

	// ���������� ����� ��������
	class CLabelDefinition : public IInstruction {
	public:
		CLabelDefinition( std::shared_ptr<CLabel>& theLabel ) : label( theLabel ) {}
		std::shared_ptr<CLabel> GetLabel();
		virtual std::wstring ToCode() override;

	private:
		std::shared_ptr<CLabel> label;

	};

	// ������������ ����������
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

	// �������� ����������� ������. ��������, �.�. ������� ��� ��������� ������������ ������ �� ��������� � �����
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

	// �������� ������ �������. �������� - �.�. ������� ������������������ ������ ������������
	// ���������� (ABI: __stdcall, __fastcall, cdecl � �.�.) � ���������� ��������� �������� ��������� (TODO)
	class CCallOperation : public COperation {
	public:
		CCallOperation( const std::shared_ptr<CLabel>& label ) : COperation( OT_Move )
		{
			GetJumpPoints().push_back( label );
		}

		virtual std::wstring ToCode();
	};

} // namespace CodeGeneration
