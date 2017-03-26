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
		OT_XorTempConst //  ����������������� ��� ��� �������� � ���������
		
	};

	std::wstring GetOperationString( TOperationType type );

} // namespace CodeGeneartion