#pragma once

#include <string>

namespace CodeGeneration {

	enum TOperationType {
		OT_None, // �� ������������!
		OT_Move, // ������ �������������� ��������, ��� �������������� ���������
		OT_MemFramePointerPlusConst, // ��������� � ISP + ���������
		OT_MemRegPlusConst, // ��������� ������� + ���������
		OT_MemRegMinusConst, // ��������� ������� - ���������
		OT_MemConstMinusReg, // ��������� ��������� - �������
		OT_MemRegMulConst, // ��������� ������� * ���������
		OT_MemConst, // ��������� � ������ �� ��������e
		OT_MemReg, // ��������� � ������ �� �������� �� ��������
		OT_Call, // ����� �������
		OT_AddConstToFirst, // ���������� � ������� ��������� � �.�.
		OT_AddTemps, // �������� �������� �������� ���������
		OT_SubTemps, // �������� �������� ��������� ���������
		OT_MulTemps, // �������� �������� ��������� ���������
		OT_DivTemps, // �������� �������� ������� ���������
		OT_AddTempConst, // �������� �������� �������� �������� � ����������
		OT_SubTempConst, // �������� �������� ��������� �������� � ����������
		OT_MulTempConst, // �������� �������� ��������� �������� � ����������
		OT_DivTempConst, // �������� �������� ������� �������� � ����������
		OT_LoadConst, // ���������� ��������� � �������
		OT_CMP, // ���������
		OT_JMP, // ����������� ������
		OT_JE,  // ���� ��� ����� // ZF = 1
		OT_JNE, // �� ���� ��� �� ����� // ZF = 0
		OT_JG,	// ������ / �� ������ � �� ����� // ZF = 0 � SF = OF
		OT_JGE, // JNL ������ ��� ����� / �� ������ // SF = OF
		OT_JL,	// JNGE ������ / �� ������ � �� ����� // SF != OF
		OT_JLE	// JNG ������ ��� ����� / �� ������	// ZF = 1 ��� SF != OF
	};

	std::wstring GetOperationString( TOperationType type );

} // namespace CodeGeneartion