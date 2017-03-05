#include <cassert>
#include <memory>
#include "EseqUpperVisitor.h"

#define NEW std::make_shared


namespace IRTree {

	static bool isNop( std::shared_ptr<IRTStatement> value )
	{
		std::shared_ptr<IRTSExp> exp = std::dynamic_pointer_cast<IRTSExp>(value);
		return exp != 0 && std::dynamic_pointer_cast<IRTree::IRTEConst>(exp->GetExp()) != 0;
	}

	static bool commute( std::shared_ptr<IRTStatement> a, std::shared_ptr<IRTExpList> b )
	{
		return isNop( a ) || std::dynamic_pointer_cast<IRTEName>(b) != 0
			|| std::dynamic_pointer_cast<IConst>(b) != 0;
	}

	//-----------------------------------------------------------------------------------------------------------------

	CEseqUpperVisitor::CEseqUpperVisitor( std::shared_ptr<CFrame> _frame) : frame(_frame)
	{
	}
	void CEseqUpperVisitor::Visit( const IRTExpList * node )
	{
		startMethod();
		returnExpression = NEW<IRTExpList>( visitExpression<IRTExpression>( node->GetHead() ), visitExpression<IRTExpList>( node->GetTail() ) );
	}

	void CEseqUpperVisitor::Visit( const IRTEConst * node )
	{
		startMethod();
		returnExpression = NEW<IRTEConst>( node->GetValue() );
	}

	void CEseqUpperVisitor::Visit( const IRTEName * node )
	{
		startMethod();
		returnExpression = NEW<IRTEName>( node->GetLabel() );
	}

	void CEseqUpperVisitor::Visit( const IRTETemp * node )
	{
		startMethod();
		returnExpression = NEW<IRTETemp>( node->GetTemp() );
	}

	void CEseqUpperVisitor::Visit( const IRTEBinop * node )
	{
		startMethod();
		RELOP op = node->GetBinop();
		std::shared_ptr<IRTExpression> eleft = visitExpression<IRTExpression>( node->GetLeft() );
		std::shared_ptr<IRTExpression> eright = visitExpression<IRTExpression>( node->GetRight() );
		std::shared_ptr<IRTEEseq> eseq = std::dynamic_pointer_cast<IRTEEseq>(eleft);
		if( eseq ) {
			std::shared_ptr<IRTStatement> s = visitStatement( eseq->GetStm() );
			std::shared_ptr<IRTExpression> e1 = visitExpression( eseq->GetExp() );
			std::shared_ptr<IRTEBinop> binop = visitExpression( NEW<IRTEBinop>( op, e1, eright ) );
			returnExpression = NEW<IRTEEseq>( s, binop );
		} else {
			eseq = std::dynamic_pointer_cast<IRTEEseq>(eright);
			if( eseq ) {
				std::shared_ptr<IRTStatement> s = visitStatement( eseq->GetStm() );
				std::shared_ptr<IRTExpression> e2 = visitExpression( eseq->GetExp() );
				std::shared_ptr<IRTETemp> t = NEW<IRTETemp>( NEW<Temp>( frame->newTemp() ) );
				std::shared_ptr<IRTSMove> move = NEW<IRTSMove>( t, eleft );
				std::shared_ptr<IRTEBinop> binop = visitExpression( NEW<IRTEBinop>( op, t, e2 ) );
				returnExpression = NEW<IRTEEseq>( move, NEW<IRTEEseq>( s, binop ) );
			} else {
				returnExpression = NEW<IRTEBinop>( op, eleft, eright );
			}
		}		
	}

	void CEseqUpperVisitor::Visit( const IRTEMem * node )
	{
		startMethod();
		std::shared_ptr<IRTExpression> exp = visitExpression<IRTExpression>( node->GetExp() );
		std::shared_ptr<IRTEEseq> eseq = std::dynamic_pointer_cast<IRTEEseq>(exp);
		if( eseq ) {
			std::shared_ptr<IRTStatement> s = visitStatement<IRTStatement>( eseq->GetStm() );
			std::shared_ptr<IRTExpression> e1 = visitExpression<IRTExpression>( eseq->GetExp() );
			returnExpression = NEW<IRTEEseq>( s, NEW<IRTEMem>( e1 ) );
		} else {
			returnExpression = NEW<IRTEMem>( exp );
		}
	}

	void CEseqUpperVisitor::Visit( const IRTECall * node )
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

	void CEseqUpperVisitor::Visit( const IRTEEseq * node )
	{
		startMethod();
		std::shared_ptr<IRTStatement> s1 = visitStatement<IRTStatement>( node->GetStm() );
		std::shared_ptr<IRTExpression> exp = visitExpression<IRTExpression>( node->GetExp() );
		std::shared_ptr<IRTEEseq> eseq = std::dynamic_pointer_cast<IRTEEseq>(exp);
		if( eseq ) {
			std::shared_ptr<IRTStatement> s2 = visitStatement<IRTStatement>( eseq->GetStm());
			std::shared_ptr<IRTExpression> e = visitExpression<IRTExpression>( eseq->GetExp());
			returnExpression = NEW<IRTEEseq>( NEW<IRTSSeq>( s1, s2 ), e );
		} else {
			returnExpression = NEW<IRTEEseq>( visitStatement<IRTStatement>( node->GetStm() ), visitExpression<IRTExpression>( node->GetExp() ) );
		}		
	}

	void CEseqUpperVisitor::Visit( const IRTSMove * node )
	{
		startMethod();
		returnStatement = NEW<IRTSMove>( visitExpression<IRTExpression>( node->GetExrDst() ), visitExpression<IRTExpression>( node->GetExrSrc() ) );
	}

	void CEseqUpperVisitor::Visit( const IRTSExp * node )
	{
		startMethod();
		returnStatement = NEW<IRTSExp>( visitExpression<IRTExpression>( node->GetExp() ) );
	}

	void CEseqUpperVisitor::Visit( const IRTSJump * node )
	{
		startMethod();
		returnStatement = NEW<IRTSJump>( node->GetLabel() );

	}

	void CEseqUpperVisitor::Visit( const IRTSCjump * node )
	{
		startMethod();
		returnStatement = NEW<IRTSCjump>( node->GetRelop(), visitExpression<IRTExpression>( node->GetExpLeft() ), visitExpression<IRTExpression>( node->GetExpRight() ),
			node->GetLabelLeft(), node->GetLabelRight() );
	}

	void CEseqUpperVisitor::Visit( const IRTSSeq * node )
	{
		startMethod();
		returnStatement = NEW<IRTSSeq>( visitStatement<IRTStatement>( node->GetStmLeft() ), visitStatement<IRTStatement>( node->GetStmRight() ) );
	}

	void CEseqUpperVisitor::Visit( const IRTSLabel * node )
	{
		startMethod();
		returnStatement = NEW<IRTSLabel>( node->GetLabel() );
	}

	void CEseqUpperVisitor::Visit( const IAccess * node )
	{
		startMethod();
		returnExpression = NEW<IAccess>( *node );

	}

	void CEseqUpperVisitor::Visit( const IRTEConstBool * node )
	{
		startMethod();
		returnExpression = NEW<IRTEConstBool>( node->GetValue() );
	}


	std::shared_ptr<IRTStatement> CEseqUpperVisitor::GetResult()
	{
		return returnStatement;
	}

	void CEseqUpperVisitor::startVisit()
	{
		assert( returnExpression == 0 );
		assert( returnStatement == 0 );
	}

	void CEseqUpperVisitor::startMethod()
	{
		assert( returnExpression == 0 );
		assert( returnStatement == 0 );
	}
}