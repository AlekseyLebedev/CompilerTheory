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
		OT_SubTempConstLeft, // �������� �������� ��������� �������� � ���������� �����
		OT_SubTempConstRight, // �������� �������� ��������� �������� � ���������� ������
		OT_MulTempConst, // �������� �������� ��������� �������� � ����������
		OT_DivTempConstLeft, // �������� �������� ������� �������� � ���������� �����
		OT_DivTempConstRight, // �������� �������� ������� �������� � ���������� ������
		OT_LoadConst, // ���������� ��������� � �������
		OT_AndTemps, // ���������� �������� � � ����������
		OT_OrTemps, // ���������� �������� ��� � ����������
		OT_XorTemps, // ����������������� ��� ��� ���������
		OT_AndTempConst, // ���������� �������� � � ��������� � ����������
		OT_OrTempConst, // ���������� �������� ��� � ��������� � ����������
		OT_XorTempConst, //  ����������������� ��� ��� �������� � ���������
		OT_CMP, // ��������� ���������
		OT_CMPC, // ��������� � ���������� 
		OT_JMP, // ����������� ������
		OT_JE,  // ���� ��� ����� // ZF = 1
		OT_JNE, // �� ���� ��� �� ����� // ZF = 0
		OT_JG,	// ������ / �� ������ � �� ����� // ZF = 0 � SF = OF
		OT_JGE, // JNL ������ ��� ����� / �� ������ // SF = OF
		OT_JL,	// JNGE ������ / �� ������ � �� ����� // SF != OF
		OT_JLE,	// JNG ������ ��� ����� / �� ������	// ZF = 1 ��� SF != OF
		OT_Movem, //MOVE from MEM to MEM 
		OT_Store, // Store
		OT_StoreConst, // Store c ����� ����������
		OT_StoreTemp, // Store c ����� Temp
	};

	std::wstring GetOperationString( TOperationType type );

} // namespace CodeGeneartion