#pragma once

#include <string>

enum TOperationType {
	OT_None, // �� ������������!
	OT_Move, // ������ �������������� ��������, ��� �������������� ���������
	OT_MemFramePointerPlusCont, // ��������� � ISP + ���������
	OT_AddConstToFirst // ���������� � ������� ��������� � �.�.
};

std::wstring GetOperationString( TOperationType type );