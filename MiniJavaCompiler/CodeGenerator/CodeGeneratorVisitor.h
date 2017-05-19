#pragma once
#include <vector>
#include <memory>

#include "..\IRTree\IRTBuilderVisitor.h"
#include "Instruction.h"

namespace CodeGeneration {

	class CCodeGeneratorVisitor : public IRTree::IVisitor {
	public:
		CCodeGeneratorVisitor();

		// Унаследовано через IVisitor
		virtual void Visit( const IRTree::IRTExpList * node ) override;
		virtual void Visit( const IRTree::IRTEConst * node ) override;
		virtual void Visit( const IRTree::IRTEName * node ) override;
		virtual void Visit( const IRTree::IRTETemp * node ) override;
		virtual void Visit( const IRTree::IRTEBinop * node ) override;
		virtual void Visit( const IRTree::IRTEMem * node ) override;
		virtual void Visit( const IRTree::IRTECall * node ) override;
		virtual void Visit( const IRTree::IRTEEseq * node ) override;
		virtual void Visit( const IRTree::IRTSMove * node ) override;
		virtual void Visit( const IRTree::IRTSExp * node ) override;
		virtual void Visit( const IRTree::IRTSJump * node ) override;
		virtual void Visit( const IRTree::IRTSCjump * node ) override;
		virtual void Visit( const IRTree::IRTSSeq * node ) override;
		virtual void Visit( const IRTree::IRTSLabel * node ) override;
		virtual void Visit( const IRTree::IAccess * node ) override;
		virtual void Visit( const IRTree::IRTEConstBool * node ) override;

		void SetFrame( std::shared_ptr<IRTree::CFrame> frame );
		CSharedPtrVector<IInstruction> GetCode() const;
	private:
		std::shared_ptr<CTemp> returnValue;
		CSharedPtrVector<IInstruction> code;
		std::shared_ptr<IRTree::CFrame> frame;
		bool hasCall;
		CSharedPtrVector<CTemp> callArguments;

		std::shared_ptr<CTemp> visitExpression( std::shared_ptr<IRTree::IRTExpression> node )
		{
			startVisit();
			if( node == 0 ) {
				return 0;
			} else {
				node->Accept( this );
				std::shared_ptr<CTemp> result = returnValue;
				assert( result != 0 );
				returnValue = 0;
				return result;
			}
		}

		void visitStatement( std::shared_ptr<IRTree::IRTStatement> node )
		{
			startVisit();
			if( node != 0 ) {
				node->Accept( this );
				assert( returnValue == 0 );
			}
		}

		inline std::shared_ptr<CTemp> newTemp()
		{
			return std::make_shared<CTemp>( frame->NewTemp() );
		}

		void startVisit();
		void startMethod();
		void universalBinopVisit( IRTree::RELOP opType, std::shared_ptr<IRTree::IRTExpression> left, std::shared_ptr<IRTree::IRTExpression> right );
	};

} // namespace CodeGeneration
