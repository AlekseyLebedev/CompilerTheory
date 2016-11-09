#pragma once

#include <string>
#include <map>
#include <list>
#include "Symbol.h"
#include "Info.h"

typedef std::map< CSymbol, IInfo > block;

// ������� ��������
class CTable {
public:
	// ��������� ����� ���� � �������
	void addBlock();
	// ������� ������� ����
	void deleteBlock();
	// ������� ��������� ����
	void deleteBlock( block* theBlock );

	void insertSymbol( const CSymbol& theSymbol, const IInfo& theInfo );
	void popSymbol( const std::string& theName );
	// ��� ��������� �������� ��� �������� ����� ���������� ���������� �� �������
	void popSymbol( const std::string& theName, const IInfo& theInfo );

	// TODO: ���������� ��������
	// ����� ��� ������ ���������� � ������� (������� ��� ���������� ������)
	const IInfo lookup( const CSymbol& theSymbol ) const;
	// ����� ��� ������ ���������� � ������� �� ��������(������� ��� ���������� ������)
	const IInfo lookup( const std::string& theSymbolName ) const;

private:
	//������� ���������� : ������ ������
	//��� ����� �� ��������� ������� � ������� ����� ���� � �������� ���������� � ����
	//��� ������ �� ������� � ������� ��������� ����
	std::list< block > table;

	// ��������� �� ������� ����
	block* currentBlock;
};