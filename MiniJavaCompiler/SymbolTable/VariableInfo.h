#pragma once

namespace SymbolTable {

	// TODO: ��� ���������� � ��������� ������� ������ ���� ��������� � ����� �����

	// ���������� � ����������
	class CVariableInfo {
	public:
		std::shared_ptr<AbstractTreeGenerator::IType> GetType();
	};
}