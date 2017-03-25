#pragma once
#include <memory>
#include <map>
#include <cassert>
#include <list>
#include "IRTree\IRTreeAllClasses.h"
#include "IRTree\CodeFragment.h"

using namespace IRTree;

class CGenerator {
public:
	CGenerator( std::shared_ptr<IRTree::CCodeFragment>  theRoot ) : root ( theRoot ) {}
	void SetRoot( std::shared_ptr<IRTree::CCodeFragment>  theRoot );
	std::shared_ptr<IRTree::CCodeFragment> GetRoot();


	void SplitIRTree();
	// ���������, �������� �� ������ Seq ������� ������ ������
	bool CheckNewLabel( std::shared_ptr<IRTStatement> theStm );
	void AddBasicBlock( std::shared_ptr<IRTStatement> block );

private:
	std::shared_ptr<IRTree::CCodeFragment>  root;
	
	// ������ ������ ���� ������ � ���� ���������� �� ������������ �������
	std::list<std::shared_ptr<IRTStatement> > basicBlocks;

	// ���������� ������� ��� CJUMP � ����� TRUE � FALSE, ����� ����� ��������
	struct CSwapBranches {		
		std::list<std::shared_ptr<IRTStatement>>::iterator trueIterator;
		std::list<std::shared_ptr<IRTStatement>>::iterator falseIterator;		
		std::shared_ptr<Label> trueLabel;
		std::shared_ptr<Label> falseLabel;

	};
	std::list<CSwapBranches> swapBranches;
};