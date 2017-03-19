#include "Generator.h"

void CGenerator::SetRoot( std::shared_ptr<IRTree::CCodeFragment>  theRoot )
{
	root = theRoot;
}

std::shared_ptr<IRTree::CCodeFragment>  CGenerator::GetRoot()
{
	return root;
}

void CGenerator::SplitIRTree()
{
	std::shared_ptr<IRTree::CCodeFragment> currentCodeFragment = root;
	while( currentCodeFragment != 0 ) {
		std::shared_ptr<IRTStatement> currentStatement = currentCodeFragment->GetTree();

		while( currentStatement != 0 ) {
			std::shared_ptr<IRTSSeq> currentSeq = std::dynamic_pointer_cast<IRTSSeq>( currentStatement );
			assert( currentSeq != 0 );

			std::shared_ptr<IRTStatement> leftStm = currentSeq->GetStmLeft();
			std::shared_ptr<IRTStatement> rightStm = currentSeq->GetStmRight();
			assert( std::dynamic_pointer_cast<IRTSSeq>( leftStm ) == 0 );

			AddBasicBlock( leftStm );

			if( std::dynamic_pointer_cast<IRTSSeq>(rightStm) != 0 ) {
				currentStatement = rightStm;
			} else {
				AddBasicBlock( rightStm );
				currentStatement = 0;
			}
		}
		currentCodeFragment = currentCodeFragment->GetNext();
	}
}

void CGenerator::AddBasicBlock( std::shared_ptr<IRTStatement> block )
{
	// TODO : добавить добавление лейблов при добавлении блоков
	basicBlocks.push_back( block );
}
