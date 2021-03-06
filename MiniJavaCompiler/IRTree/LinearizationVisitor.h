#include <vector>
#include "IRTreeAllClasses.h"
#include "IVisitor.h"
#include "Frame.h"

namespace IRTree {

	class CLinearizationVisitor : public IVisitor {
	public:
		CLinearizationVisitor( std::shared_ptr<CFrame>, bool call );
		// ������������ ����� IVisitor
		virtual void Visit( const IRTExpList * node ) override;
		virtual void Visit( const IRTEConst * node ) override;
		virtual void Visit( const IRTEName * node ) override;
		virtual void Visit( const IRTETemp * node ) override;
		virtual void Visit( const IRTEBinop * node ) override;
		virtual void Visit( const IRTEMem * node ) override;
		virtual void Visit( const IRTECall * node ) override;
		virtual void Visit( const IRTEEseq * node ) override;
		virtual void Visit( const IRTSMove * node ) override;
		virtual void Visit( const IRTSExp * node ) override;
		virtual void Visit( const IRTSJump * node ) override;
		virtual void Visit( const IRTSCjump * node ) override;
		virtual void Visit( const IRTSSeq * node ) override;
		virtual void Visit( const IRTSLabel * node ) override;
		virtual void Visit( const IAccess * node ) override;
		virtual void Visit( const IRTEConstBool * node ) override;

		std::shared_ptr<IRTStatement> GetResult();
	private:
		std::shared_ptr<IRTStatement> returnStatement;
		std::shared_ptr<IRTExpression> returnExpression;
		std::vector<std::shared_ptr<IRTExpression> > arguments;
		std::vector<std::shared_ptr<Temp> > temps;
		bool hasCall;
		bool callRemove;

		std::shared_ptr<CFrame> frame;
		template<typename T>
		std::shared_ptr<typename T> visitExpression( std::shared_ptr<typename T> node )
		{
			startVisit();
			IRTExpression* forAssert = node.get();
			if( node == 0 ) {
				return 0;
			} else {
				node->Accept( this );
				std::shared_ptr<typename T> result = std::dynamic_pointer_cast<T>(returnExpression);
				assert( result != 0 );
				returnExpression = 0;
				return result;
			}
		}

		template<typename T>
		std::shared_ptr<typename T> visitStatement( std::shared_ptr<typename T> node )
		{
			startVisit();
			IRTStatement* forAssert = node.get();
			if( node == 0 ) {
				return 0;
			} else {
				node->Accept( this );
				std::shared_ptr<typename T> result = std::dynamic_pointer_cast<T>(returnStatement);
				assert( result != 0 );
				returnStatement = 0;
				return result;
			}
		}

		std::shared_ptr<IRTExpression> regenerateByArguments( std::shared_ptr<IRTExpression> node, std::vector<std::shared_ptr<IRTExpression>>&, std::vector<std::shared_ptr<Temp>>& );
		std::shared_ptr<IRTExpression> regenerateByField( std::shared_ptr<IRTExpression> root, std::vector<std::shared_ptr<IRTExpression>>& oldArgumntes, std::vector<std::shared_ptr<Temp>>& oldTemps );
		void startVisit();
		void startMethod();
	};
}
