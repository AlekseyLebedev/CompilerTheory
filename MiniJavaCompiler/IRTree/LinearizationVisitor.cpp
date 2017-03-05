#include <cassert>
#include <memory>
#include "LinearizationVisitor.h"

#define NEW std::make_shared


namespace IRTree {
	CLinearizationVisitor::CLinearizationVisitor( std::shared_ptr<CFrame> _frame) : frame(_frame)
	{
	}
	void CLinearizationVisitor::Visit( const IRTExpList * node )
	{
		startMethod();
		returnExpression = NEW<IRTExpList>( visitExpression<IRTExpression>( node->GetHead() ), visitExpression<IRTExpList>( node->GetTail() ) );
	}

	void CLinearizationVisitor::Visit( const IRTEConst * node )
	{
		startMethod();
		returnExpression = NEW<IRTEConst>( node->GetValue() );
	}

	void CLinearizationVisitor::Visit( const IRTEName * node )
	{
		startMethod();
		returnExpression = NEW<IRTEName>( node->GetLabel() );
	}

	void CLinearizationVisitor::Visit( const IRTETemp * node )
	{
		startMethod();
		returnExpression = NEW<IRTETemp>( node->GetTemp() );
	}

	void CLinearizationVisitor::Visit( const IRTEBinop * node )
	{
		startMethod();
		returnExpression = NEW<IRTEBinop>( node->GetBinop(), visitExpression<IRTExpression>( node->GetLeft() ), visitExpression<IRTExpression>( node->GetRight() ) );
	}

	void CLinearizationVisitor::Visit( const IRTEMem * node )
	{
		startMethod();
		returnExpression = NEW<IRTEMem>( visitExpression<IRTExpression>( node->GetExp() ) );
	}

	void CLinearizationVisitor::Visit( const IRTECall * node )
	{
		startMethod();
		std::shared_ptr<IRTExpList> args = visitExpression<IRTExpList>( node->GetArgs() );
		std::shared_ptr<IRTECall> call = std::dynamic_pointer_cast<IRTECall>(args->GetHead());
		if( call ) {
			std::shared_ptr<IRTETemp> newTemp = NEW<IRTETemp>(NEW<Temp>( frame->newTemp() ));
			returnExpression = NEW<IRTEEseq>( NEW<IRTSMove>(call,newTemp), 
				NEW<IRTECall>( visitExpression<IRTExpression>( node->GetFunc() ), NEW<IRTExpList>( newTemp, args->GetTail() ) ));
		} else {
			returnExpression = NEW<IRTECall>( visitExpression<IRTExpression>( node->GetFunc() ), visitExpression<IRTExpList>( node->GetArgs() ) );
		}
	}

	void CLinearizationVisitor::Visit( const IRTEEseq * node )
	{
		startMethod();
		returnExpression = NEW<IRTEEseq>( visitStatement<IRTStatement>( node->GetStm() ), visitExpression<IRTExpression>( node->GetExp() ) );
	}

	void CLinearizationVisitor::Visit( const IRTSMove * node )
	{
		startMethod();
		returnStatement = NEW<IRTSMove>( visitExpression<IRTExpression>( node->GetExrDst() ), visitExpression<IRTExpression>( node->GetExrSrc() ) );
	}

	void CLinearizationVisitor::Visit( const IRTSExp * node )
	{
		startMethod();
		returnStatement = NEW<IRTSExp>( visitExpression<IRTExpression>( node->GetExp() ) );
	}

	void CLinearizationVisitor::Visit( const IRTSJump * node )
	{
		startMethod();
		returnStatement = NEW<IRTSJump>( node->GetLabel() );

	}

	void CLinearizationVisitor::Visit( const IRTSCjump * node )
	{
		startMethod();
		returnStatement = NEW<IRTSCjump>( node->GetRelop(), visitExpression<IRTExpression>( node->GetExpLeft() ), visitExpression<IRTExpression>( node->GetExpRight() ),
			node->GetLabelLeft(), node->GetLabelRight() );
	}

	void CLinearizationVisitor::Visit( const IRTSSeq * node )
	{
		startMethod();
		returnStatement = NEW<IRTSSeq>( visitStatement<IRTStatement>( node->GetStmLeft() ), visitStatement<IRTStatement>( node->GetStmRight() ) );
	}

	void CLinearizationVisitor::Visit( const IRTSLabel * node )
	{
		startMethod();
		returnStatement = NEW<IRTSLabel>( node->GetLabel() );
	}

	void CLinearizationVisitor::Visit( const IAccess * node )
	{
		startMethod();
		// TODO

	}

	void CLinearizationVisitor::Visit( const IRTEConstBool * node )
	{
		startMethod();
		returnExpression = NEW<IRTEConstBool>( node->GetValue() );
	}


	std::shared_ptr<IRTStatement> CLinearizationVisitor::GetResult()
	{
		return returnStatement;
	}

	void CLinearizationVisitor::startVisit()
	{
		assert( returnExpression == 0 );
		assert( returnStatement == 0 );
	}

	void CLinearizationVisitor::startMethod()
	{
		assert( returnExpression == 0 );
		assert( returnStatement == 0 );
	}
}