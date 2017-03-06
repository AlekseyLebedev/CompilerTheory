#include <cassert>
#include <memory>
#include "AccessRemoverVisitor.h"
#include "Frame.h"

#define NEW std::make_shared


namespace IRTree {
	CAccessRemoverVisitor::CAccessRemoverVisitor( std::shared_ptr<CFrame> _frame ) : frame( _frame )
	{
	}

	void CAccessRemoverVisitor::Visit( const IRTExpList * node )
	{
		startMethod();
		returnExpression = NEW<IRTExpList>( visitExpression<IRTExpression>( node->GetHead() ), visitExpression<IRTExpList>( node->GetTail() ) );
	}

	void CAccessRemoverVisitor::Visit( const IRTEConst * node )
	{
		startMethod();
		returnExpression = NEW<IRTEConst>( node->GetValue() );
	}

	void CAccessRemoverVisitor::Visit( const IRTEName * node )
	{
		startMethod();
		returnExpression = NEW<IRTEName>( node->GetLabel() );
	}

	void CAccessRemoverVisitor::Visit( const IRTETemp * node )
	{
		startMethod();
		returnExpression = NEW<IRTETemp>( node->GetTemp() );
	}

	void CAccessRemoverVisitor::Visit( const IRTEBinop * node )
	{
		startMethod();
		returnExpression = NEW<IRTEBinop>( node->GetBinop(), visitExpression<IRTExpression>( node->GetLeft() ), visitExpression<IRTExpression>( node->GetRight() ) );
	}

	void CAccessRemoverVisitor::Visit( const IRTEMem * node )
	{
		startMethod();
		returnExpression = NEW<IRTEMem>( visitExpression<IRTExpression>( node->GetExp() ) );
	}

	void CAccessRemoverVisitor::Visit( const IRTECall * node )
	{
		startMethod();
		returnExpression = NEW<IRTECall>( visitExpression<IRTExpression>( node->GetFunc() ), visitExpression<IRTExpList>( node->GetArgs() ) );
	}

	void CAccessRemoverVisitor::Visit( const IRTEEseq * node )
	{
		startMethod();
		returnExpression = NEW<IRTEEseq>( visitStatement<IRTStatement>( node->GetStm() ), visitExpression<IRTExpression>( node->GetExp() ) );
	}

	void CAccessRemoverVisitor::Visit( const IRTSMove * node )
	{
		startMethod();
		returnStatement = NEW<IRTSMove>( visitExpression<IRTExpression>( node->GetExrDst() ), visitExpression<IRTExpression>( node->GetExrSrc() ) );
	}

	void CAccessRemoverVisitor::Visit( const IRTSExp * node )
	{
		startMethod();
		returnStatement = NEW<IRTSExp>( visitExpression<IRTExpression>( node->GetExp() ) );
	}

	void CAccessRemoverVisitor::Visit( const IRTSJump * node )
	{
		startMethod();
		returnStatement = NEW<IRTSJump>( node->GetLabel() );

	}

	void CAccessRemoverVisitor::Visit( const IRTSCjump * node )
	{
		startMethod();
		returnStatement = NEW<IRTSCjump>( node->GetRelop(), visitExpression<IRTExpression>( node->GetExpLeft() ), visitExpression<IRTExpression>( node->GetExpRight() ),
			node->GetLabelLeft(), node->GetLabelRight() );
	}

	void CAccessRemoverVisitor::Visit( const IRTSSeq * node )
	{
		startMethod();
		returnStatement = NEW<IRTSSeq>( visitStatement<IRTStatement>( node->GetStmLeft() ), visitStatement<IRTStatement>( node->GetStmRight() ) );
	}

	void CAccessRemoverVisitor::Visit( const IRTSLabel * node )
	{
		startMethod();
		returnStatement = NEW<IRTSLabel>( node->GetLabel() );
	}

	void CAccessRemoverVisitor::Visit( const IAccess * node )
	{
		startMethod();
		if( node->GetName() == CFrame::ReturnName ) {
			assert( node->GetOffset() == 0 );
			returnExpression = frame->GetThisAccess();
		} else {
			returnExpression = NEW<IRTEMem>( NEW<IRTEBinop>( BINOP_PLUS, frame->GetFramePointerAccess(), NEW<IRTEConst>( node->GetOffset() ) ) );
		}

	}

	void CAccessRemoverVisitor::Visit( const IRTEConstBool * node )
	{
		startMethod();
		returnExpression = NEW<IRTEConstBool>( node->GetValue() );
	}


	std::shared_ptr<IRTStatement> CAccessRemoverVisitor::GetResult()
	{
		return returnStatement;
	}

	void CAccessRemoverVisitor::startVisit()
	{
		assert( returnExpression == 0 );
		assert( returnStatement == 0 );
	}

	void CAccessRemoverVisitor::startMethod()
	{
		assert( returnExpression == 0 );
		assert( returnStatement == 0 );
	}
}