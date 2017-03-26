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
		OT_AddConstToFirst, // ���������� � ������� ��������� � �.�.
		OT_AddTemps, // �������� �������� �������� ���������
		OT_SubTemps, // �������� �������� ��������� ���������
		OT_MulTemps, // �������� �������� ��������� ���������
		OT_DivTemps, // �������� �������� ������� ���������
		OT_AddTempConst, // �������� �������� �������� �������� � ����������
		OT_SubTempConst, // �������� �������� ��������� �������� � ����������
		OT_MulTempConst, // �������� �������� ��������� �������� � ����������
		OT_DivTempConst, // �������� �������� ������� �������� � ����������
		OT_LoadConst // ���������� ��������� � �������
	};

	std::wstring GetOperationString( TOperationType type );

} // namespace CodeGeneartion