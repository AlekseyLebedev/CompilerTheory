#pragma once
#include <memory>
#include <map>
#include <cassert>
#include <list>
#include "..\IRTree\IRTreeAllClasses.h"
#include "..\IRTree\CodeFragment.h"

using namespace IRTree;

class CGenerator {
public:
	CGenerator( std::shared_ptr<IRTree::CCodeFragment>  theRoot ) : root ( theRoot ) {}
	void SetRoot( std::shared_ptr<IRTree::CCodeFragment>  theRoot );
	std::shared_ptr<IRTree::CCodeFragment> GetRoot();

	std::list<std::pair<std::shared_ptr<IRTStatement>, std::shared_ptr<CFrame> > > GetBasicBlocks() const;

	void SplitIRTree();
	// ���������, �������� �� ������ Seq ������� ������ ������
	bool CheckNewLabel( std::shared_ptr<IRTStatement> theStm );
	void AddBasicBlock( std::shared_ptr<IRTStatement> block );

private:
	std::shared_ptr<IRTree::CCodeFragment>  root;
	std::shared_ptr<CFrame> currentFrame;
	// ������ ������ ���� ������ � ���� ���������� �� ������������ �������
	std::list<std::pair<std::shared_ptr<IRTStatement>, std::shared_ptr<CFrame> > > basicBlocks;

	// ���������� ������� ��� CJUMP � ����� TRUE � FALSE, ����� ����� ��������
	struct CSwapBranches {		
		std::list<std::pair<std::shared_ptr<IRTStatement>, std::shared_ptr<CFrame> > >::iterator trueIterator;
		std::list<std::pair<std::shared_ptr<IRTStatement>, std::shared_ptr<CFrame> > >::iterator falseIterator;
		std::shared_ptr<Label> trueLabel;
		std::shared_ptr<Label> falseLabel;

	};
	std::list<CSwapBranches> swapBranches;
};