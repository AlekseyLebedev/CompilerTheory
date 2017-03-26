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
		currentFrame = currentCodeFragment->GetFrame();
		while( currentStatement != 0 ) {
			std::shared_ptr<IRTSSeq> currentSeq = std::dynamic_pointer_cast<IRTSSeq>( currentStatement );
			assert( currentSeq != 0 );
			std::shared_ptr<IRTSSeq> oldRight = currentSeq;

			std::shared_ptr<IRTStatement> leftStm = currentSeq->GetStmLeft();
			assert( std::dynamic_pointer_cast<IRTSSeq>( leftStm ) == 0 );
			std::shared_ptr<IRTStatement> rightStm = currentSeq->GetStmRight();

			while( std::dynamic_pointer_cast<IRTSSeq>( rightStm ) != 0 && CheckNewLabel( rightStm ) ) {
				std::shared_ptr<IRTSSeq> tmp = std::dynamic_pointer_cast<IRTSSeq>( rightStm );
				assert( tmp != 0 );
				leftStm = tmp->GetStmLeft();
				oldRight = tmp;
				rightStm = tmp->GetStmRight();
			}

			// правый оказался Seq, т.е. дошли до нового лейбла
			if( std::dynamic_pointer_cast<IRTSSeq>( rightStm ) != 0 ) {
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
	assert( std::dynamic_pointer_cast<IRTSSeq>( leftStm ) == 0 );

	if( std::dynamic_pointer_cast<IRTSLabel>( leftStm ) != 0 ) {
		return false;
	}
	return true;
}

void CGenerator::AddBasicBlock( std::shared_ptr<IRTStatement> block )
{
	// добавление лейблов
	std::shared_ptr<IRTSSeq> seq = std::dynamic_pointer_cast<IRTSSeq>( block );
	if( seq ) {
		std::shared_ptr<IRTStatement> left = seq->GetStmLeft();
		if( !std::dynamic_pointer_cast<IRTSLabel>( left ) ) {
			block = std::make_shared<IRTSSeq>( std::make_shared<IRTSLabel>( std::make_shared<Label>() ), block );
		}
	}

	std::shared_ptr<IRTSSeq> currentSeq = std::dynamic_pointer_cast<IRTSSeq>( block );
	assert( currentSeq != 0 );
	std::shared_ptr<IRTStatement> oldRight = block;
	std::shared_ptr<IRTStatement> rightStm = currentSeq->GetStmRight();
	std::shared_ptr<IRTStatement> rightRightStm;
	if( std::dynamic_pointer_cast<IRTSSeq>( rightStm ) != 0 ) {
		std::shared_ptr<IRTSSeq> tmp = std::dynamic_pointer_cast<IRTSSeq>( rightStm );
		assert( tmp != 0 );
		rightRightStm = tmp->GetStmRight();
	}
	while( std::dynamic_pointer_cast<IRTSSeq>(rightRightStm) != 0 ) {
		std::shared_ptr<IRTSSeq> tmp = std::dynamic_pointer_cast<IRTSSeq>(rightRightStm);
		assert( tmp != 0 );
		oldRight = rightStm;
		rightStm = rightRightStm;
		rightRightStm = tmp->GetStmRight();
	}
	std::shared_ptr<IRTSSeq> rightSeq = std::dynamic_pointer_cast<IRTSSeq>( rightStm );

	std::shared_ptr<IRTStatement> leftStm;
	if( rightSeq != 0 ) {
		leftStm = rightSeq->GetStmLeft();
		assert( std::dynamic_pointer_cast<IRTSSeq>(leftStm) == 0 );
	}

	std::shared_ptr<IRTSSeq> oldRightSeq = std::dynamic_pointer_cast<IRTSSeq>( oldRight );
	assert( oldRightSeq != 0 );
	if( rightRightStm == 0 && leftStm != 0 ) {
		oldRightSeq->SetStmRight( leftStm );
	}	

	basicBlocks.push_back( std::make_pair(block, currentFrame) );

	// swap true и false
	seq = std::dynamic_pointer_cast<IRTSSeq>(block);
	if( swapBranches.size() ) {
		std::shared_ptr<IRTSLabel> label = std::dynamic_pointer_cast<IRTSLabel>(seq->GetStmLeft());
		if( label ) {
			for( std::list<CSwapBranches>::iterator swapBrancesItem = swapBranches.begin(); swapBrancesItem != swapBranches.end();
				swapBrancesItem++ ) {
				if( label->GetLabel() == swapBrancesItem->trueLabel ) {
					swapBrancesItem->trueIterator = std::prev(basicBlocks.end());
				} else if( label->GetLabel() == swapBrancesItem->falseLabel ) {
					swapBrancesItem->falseIterator = std::prev( basicBlocks.end() );
					std::swap( *swapBrancesItem->falseIterator, *swapBrancesItem->trueIterator );
					swapBranches.erase( swapBrancesItem );
					break;
				}

			}
		}

	}
	if( seq ) {
		do {
			std::shared_ptr<IRTStatement> right = seq->GetStmRight();
			std::shared_ptr<IRTSCjump> cjump = std::dynamic_pointer_cast<IRTSCjump>(right);
			if( cjump ) {
				CSwapBranches swapBranch;
				swapBranch.trueLabel = cjump->GetLabelLeft();
				swapBranch.falseLabel = cjump->GetLabelRight();
				swapBranches.push_back( swapBranch );
				break;
			} else {
				std::shared_ptr<IRTSSeq> rseq = std::dynamic_pointer_cast<IRTSSeq>(right);
				if( rseq ) {
					seq = rseq;
				} else {
					break;
				}
			}
		} while( true );
	}
}

