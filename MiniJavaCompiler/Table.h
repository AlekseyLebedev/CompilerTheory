#pragma once

#include <string>
#include <unordered_map>
#include "Symbol.h"
#include "Info.h"

// ������� ��������
class CTable {
public:
	void insert( const CSymbol& theSymbol, const IInfo& theInfo);
	void pop(const std::string& theName );
	// ��� ��������� �������� ��� �������� ����� ���������� ���������� �� �������
	void pop(const std::string& theName, const IInfo& theInfo );
	// ����� ��� ������ ���������� � ������� (������� ��� ���������� ������)
	const IInfo lookup(const CSymbol& theSymbol ) const;

private:
	// �� ������ ��� ������ ���� ������ ���
	std::unordered_map < CSymbol, IInfo > table;
};