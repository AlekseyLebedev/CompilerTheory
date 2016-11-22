#pragma once

#include <string>
#include <vector>
#include "Symbol.h"
#include "ClassInfo.h"
#include "MethodInfo.h"
#include "VariableInfo.h"
#include "..\AbstractTreeGenerator\StringTable.h"

namespace SymbolTable {

	// ������� ��������
	class CTable {
	public:
		// ����������� �� ����� � ������
		AbstractTreeGenerator::CStringTable stringTable;
		// ����������� �� ������� � CSymbol
		std::vector<CSymbol> v;
		// ������� ��� ��� �����


		////  ����� ������ �����
		//// ��������� ����� ���� � �������
		//void addBlock();
		//// ������� ��������� ����, ����� ���������� ���������� ��������� �� ������� ����
		//void deleteBlock();
		//// ������� ��������� ����, ��� �������� ���������� �����
		//void deleteBlock( std::list< block* >::iterator theBlockIter );

		//void insertSymbol( const CSymbol& theSymbol, const IInfo& theInfo );
		//// ������� ������ �� �����
		//void popSymbol( const std::string& theName );
		//// ��� �������� ����� ���������� ���������� �� �������
		//void popSymbol( const std::string& theName, const IInfo& theInfo );
		//// �������� �������� �� ������� ����
		//std::list< block* >::iterator getCurrentBlockIter();
		//
		//// ����� ��� ������ ���������� � ������� (������� ��� ���������� ������)
		//std::pair< block::iterator, bool > find( const CSymbol& theSymbol );
		//// ����� ��� ������ ���������� � ������� �� ��������(������� ��� ���������� ������)
		//std::pair< block::iterator, bool > find( const std::string& theSymbolName );

	private:
		////������� ���������� : ������ ������
		////��� ����� �� ��������� ������� � ������� ����� ���� � �������� ���������� � ����
		////��� ������ �� ������� � ������� ��������� ����
		//std::list< block* > table;

		////// ��������� �� ������� ����
		////block* currentBlock;
		//// �������� �� ������� ����
		//std::list< block* >::iterator currentBlockIter;
	};
}