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
			std::shared_ptr<IRTSSeq> oldRight = currentSeq;

			std::shared_ptr<IRTStatement> leftStm = currentSeq->GetStmLeft();
			assert( std::dynamic_pointer_cast<IRTSSeq>(leftStm) == 0 );
			std::shared_ptr<IRTStatement> rightStm = currentSeq->GetStmRight();

			while( std::dynamic_pointer_cast<IRTSSeq>( rightStm ) != 0 && CheckNewLabel( rightStm ) ) {
				std::shared_ptr<IRTSSeq> tmp = std::dynamic_pointer_cast<IRTSSeq>( rightStm );
				assert( tmp != 0 );
				leftStm = tmp->GetStmLeft();
				oldRight = tmp;
				rightStm = tmp->GetStmRight();
			}

			// правый оказался Seq, т.е. дошли до нового лейбла
			if( std::dynamic_pointer_cast<IRTSSeq>(rightStm) != 0 ) {
				oldRight->CutStmRight();
				currentStatement = rightStm;
				rightStm = nullptr;
				AddBasicBlock( currentSeq );
			}  else {
			// правый оказался не Seq, т.е. дошли до конца и добавляем все что осталось
				AddBasicBlock( currentSeq );
				currentStatement = 0;
			}
		}
		currentCodeFragment = currentCodeFragment->GetNext();
	}
}

bool CGenerator::CheckNewLabel( std::shared_ptr<IRTStatement> theStm )
{
	std::shared_ptr<IRTSSeq> currentSeq = std::dynamic_pointer_cast<IRTSSeq>( theStm );
	assert( currentSeq != 0 );
	std::shared_ptr<IRTStatement> leftStm = currentSeq->GetStmLeft();
	std::shared_ptr<IRTStatement> rightStm = currentSeq->GetStmRight();
	assert( std::dynamic_pointer_cast<IRTSSeq>(leftStm) == 0 );

	if( std::dynamic_pointer_cast<IRTSLabel>(leftStm) != 0 ) {
		return false;
	}
	return true;
}
// TODO : добавить добавление лейблов при добавлении блоков
void CGenerator::AddBasicBlock( std::shared_ptr<IRTStatement> block )
{
	// обрезка правого поддерева
	std::shared_ptr<IRTSSeq> seq = std::dynamic_pointer_cast<IRTSSeq>(block);
	if( seq ) {
		std::shared_ptr<IRTStatement> left = seq->GetStmLeft();
		if( !std::dynamic_pointer_cast<IRTSLabel>(left) ) {
			basicBlocks.push_back(std::make_shared<IRTSSeq>(
				std::make_shared<IRTSLabel>(std::make_shared<Label>()), block ));
			return;
		}
	}


	basicBlocks.push_back( block );
}
