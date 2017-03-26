#include <cassert>
#include <memory>

#include "CodeGeneratorVisitor.h"

#define NEW std::make_shared
#define DYNAMIC_CAST std::dynamic_pointer_cast

namespace CodeGeneration {

	CCodeGeneratorVisitor::CCodeGeneratorVisitor()
	{

	}

	void CCodeGeneratorVisitor::Visit( const IRTree::IRTExpList * node )
	{
		startMethod();
		assert( false ); //TODO
	}

	void CCodeGeneratorVisitor::Visit( const IRTree::IRTEConst * node )
	{
		startMethod();
		// ƒолжны найти это при разборе случаев сверху
		assert( false );
	}

	void CCodeGeneratorVisitor::Visit( const IRTree::IRTEName * node )
	{
		startMethod();
		assert( false ); //TODO
	}

	void CCodeGeneratorVisitor::Visit( const IRTree::IRTETemp * node )
	{
		startMethod();
		assert( false ); //TODO
	}

	static int applyIntOperation( IRTree::RELOP operation, int leftArg, int rigthArg )
	{
		switch( operation ) {
			case IRTree::BINOP_DIV:
				return leftArg / rigthArg;
			case IRTree::BINOP_MINUS:
				return leftArg - rigthArg;
			case IRTree::BINOP_MOD:
				return leftArg % rigthArg;
			case IRTree::BINOP_PLUS:
				return leftArg + rigthArg;
			case IRTree::BINOP_MUL:
				return leftArg * rigthArg;
			default:
				assert( false );
				return 0xDEADBEEF;
		}
	}

	void CCodeGeneratorVisitor::Visit( const IRTree::IRTEBinop * node )
	{
		startMethod();
		IRTree::RELOP opType = node->GetBinop();
		std::shared_ptr<IRTree::IRTExpression> left = node->GetLeft();
		std::shared_ptr<IRTree::IRTExpression> right = node->GetRight();
		std::shared_ptr<IRTree::IRTEConst> leftConst = std::dynamic_pointer_cast<IRTree::IRTEConst>(left);
		std::shared_ptr<IRTree::IRTEConst> rightConst = std::dynamic_pointer_cast<IRTree::IRTEConst>(right);
		std::shared_ptr<COperation> operation;
		std::shared_ptr<CTemp> resultTemp;
		resultTemp = newTemp();

		// 1 случай: оба константы
		if( leftConst && rightConst ) {
			operation = NEW<COperation>( OT_LoadConst );
			int resultConst = applyIntOperation( node->GetBinop(), leftConst->GetValue(), rightConst->GetValue() );
			operation->GetConstants().push_back( resultConst );
			operation->GetArguments().push_back( resultTemp );
		}
		// 2 случай: один из аргументов константа, другой - регистр
		else if( (!leftConst && rightConst) || (leftConst && !rightConst) ) {
			std::shared_ptr<CTemp> temp;
			int constInt;
			if( !leftConst ) {
				assert( rightConst );
				temp = visitExpression( left );
				constInt = rightConst->GetValue();
			} else {
				assert( leftConst );
				temp = visitExpression( right );
				constInt = leftConst->GetValue();
			}

			if( temp )
				switch( opType ) {
					case IRTree::BINOP_PLUS:
						operation = NEW<COperation>( OT_AddTempConst );
						break;
					case IRTree::BINOP_MINUS:
						operation = NEW<COperation>( OT_SubTempConst );
						break;
					case IRTree::BINOP_MUL:
						operation = NEW<COperation>( OT_MulTempConst );
						break;
					case IRTree::BINOP_DIV:
						operation = NEW<COperation>( OT_DivTempConst );
						break;
					default:
						assert( false );
						break;
				}

			operation->GetArguments().push_back( resultTemp );
			operation->GetArguments().push_back( temp );
			operation->GetConstants().push_back( constInt );
		}
		// 3 случай: оба регистры
		else {
			assert( !rightConst );
			assert( !leftConst );
			std::shared_ptr<CTemp> tempLeft = visitExpression( node->GetLeft() );
			std::shared_ptr<CTemp> tempRight = visitExpression( node->GetRight() );

			switch( opType ) {
				case IRTree::BINOP_PLUS:
					operation = NEW<COperation>( OT_AddTemps );
					break;
				case IRTree::BINOP_MINUS:
					operation = NEW<COperation>( OT_SubTemps );
					break;
				case IRTree::BINOP_MUL:
					operation = NEW<COperation>( OT_MulTemps );
					break;
				case IRTree::BINOP_DIV:
					operation = NEW<COperation>( OT_DivTemps );
					break;
			}

			operation->GetArguments().push_back( resultTemp );
			operation->GetArguments().push_back( tempLeft );
			operation->GetArguments().push_back( tempRight );
		}

		operation->GetDefinedTemps().push_back( resultTemp );
		code.push_back( operation );

		returnValue = resultTemp;
	}

	inline bool isAdressOperation( IRTree::RELOP operation )
	{
		switch( operation ) {
			case IRTree::BINOP_PLUS:
			case IRTree::BINOP_MINUS:
			case IRTree::BINOP_MUL:
				return true;
			default:
				return false;
				break;
		}
	}

	void CCodeGeneratorVisitor::Visit( const IRTree::IRTEMem * node )
	{
		startMethod();
		auto expression = node->GetExp();
		std::shared_ptr<IRTree::IRTEBinop> binop = DYNAMIC_CAST<IRTree::IRTEBinop>( expression );
		if( binop != 0 ) {
			std::shared_ptr<IRTree::IRTEConst> rightConst = DYNAMIC_CAST<IRTree::IRTEConst>( binop->GetRight() );
			std::shared_ptr<IRTree::IRTEConst> leftConst = DYNAMIC_CAST<IRTree::IRTEConst>( binop->GetLeft() );
			std::shared_ptr<IRTree::IAccess> access = DYNAMIC_CAST<IRTree::IAccess>( binop->GetLeft() );
			if( isAdressOperation( binop->GetBinop() ) ) {
				if( rightConst != 0 && access != 0 ) {
					assert( access->GetName() == IRTree::CFrame::FramePointerName );
					assert( access->GetType() == IRTree::BINOP_PLUS );
					std::shared_ptr<COperation> operation = NEW<COperation>( OT_MemFramePointerPlusConst );
					returnValue = newTemp();
					operation->GetDefinedTemps().push_back( returnValue );
					operation->GetArguments().push_back( returnValue );
					code.push_back( operation );
					return;
				}

				if( rightConst != 0 ) {
					if( leftConst != 0 ) {
						int result = applyIntOperation( binop->GetBinop(), leftConst->GetValue(), rightConst->GetValue() );
						std::shared_ptr<COperation> operation = NEW<COperation>( OT_MemConst );
						returnValue = newTemp();
						operation->GetConstants().push_back( result );
						operation->GetArguments().push_back( returnValue );
						operation->GetDefinedTemps().push_back( returnValue );
						code.push_back( operation );
						return;
					} else {
						std::shared_ptr<COperation> operation;
						switch( binop->GetBinop() ) {
							case IRTree::BINOP_PLUS:
								operation = NEW<COperation>( OT_MemRegPlusConst );
								break;
							case IRTree::BINOP_MINUS:
								operation = NEW<COperation>( OT_MemRegMinusConst );
								break;
							case IRTree::BINOP_MUL:
								operation = NEW<COperation>( OT_MemRegMulConst );
								break;
							default:
								assert( false );
								return;
						}
						returnValue = newTemp();
						operation->GetArguments().push_back( returnValue );
						operation->GetDefinedTemps().push_back( returnValue );
						operation->GetArguments().push_back( visitExpression( binop->GetLeft() ) );
						operation->GetConstants().push_back( rightConst->GetValue() );
						code.push_back( operation );
						return;
					}
				} else {
					if( leftConst != 0 ) {
						std::shared_ptr<COperation> operation;
						switch( binop->GetBinop() ) {
							case IRTree::BINOP_PLUS:
								operation = NEW<COperation>( OT_MemRegPlusConst );
								break;
							case IRTree::BINOP_MINUS:
								operation = NEW<COperation>( OT_MemConstMinusReg );
								break;
							case IRTree::BINOP_MUL:
								operation = NEW<COperation>( OT_MemRegMulConst );
								break;
							default:
								assert( false );
								return;
						}
						returnValue = newTemp();
						operation->GetArguments().push_back( returnValue );
						operation->GetDefinedTemps().push_back( returnValue );
						operation->GetArguments().push_back( visitExpression( binop->GetRight() ) );
						operation->GetConstants().push_back( leftConst->GetValue() );
						code.push_back( operation );
						return;
					} else {
						std::shared_ptr<COperation> operation = NEW<COperation>( OT_MemReg );
						returnValue = newTemp();
						operation->GetDefinedTemps().push_back( returnValue );
						operation->GetArguments().push_back( returnValue );
						operation->GetArguments().push_back( visitExpression( expression ) );
						code.push_back( operation );
						return;
					}
				}
			}
			assert( false );
			returnValue = 0;
		} else {
			std::shared_ptr<IRTree::IRTEConst> constExpr = DYNAMIC_CAST<IRTree::IRTEConst>( expression );
			if( constExpr != 0 ) {
				std::shared_ptr<COperation> operation = NEW<COperation>( OT_MemConst );
				returnValue = newTemp();
				operation->GetConstants().push_back( constExpr->GetValue() );
				operation->GetArguments().push_back( returnValue );
				operation->GetDefinedTemps().push_back( returnValue );
				code.push_back( operation );
			} else {
				std::shared_ptr<COperation> operation = NEW<COperation>( OT_MemReg );
				returnValue = newTemp();
				operation->GetDefinedTemps().push_back( returnValue );
				operation->GetArguments().push_back( returnValue );
				operation->GetArguments().push_back( visitExpression( expression ) );
				code.push_back( operation );
			}
		}
	}

	void CCodeGeneratorVisitor::Visit( const IRTree::IRTECall * node )
	{
		startMethod();
		assert( false ); //TODO
	}

	void CCodeGeneratorVisitor::Visit( const IRTree::IRTEEseq * node )
	{
		startMethod();
		assert( false ); //TODO
	}

	void CCodeGeneratorVisitor::Visit( const IRTree::IRTSMove * node )
	{
		startMethod();
		assert( false ); //TODO
	}

	void CCodeGeneratorVisitor::Visit( const IRTree::IRTSExp * node )
	{
		startMethod();
		assert( false ); //TODO
	}

	void CCodeGeneratorVisitor::Visit( const IRTree::IRTSJump * node )
	{
		startMethod();
		std::shared_ptr<COperation> operation = NEW<COperation>( OT_JMP );

		auto label = node->GetLabel();
		operation->GetJumpPoints().push_back( label );
		
		code.push_back( operation );
	}

	void CCodeGeneratorVisitor::Visit( const IRTree::IRTSCjump * node )
	{
		startMethod();

		auto labelLeft = node->GetLabelLeft();
		std::shared_ptr<COperation> operationLeft = NEW<COperation>( OT_JE );
		operationLeft->GetJumpPoints().push_back( labelLeft );
		code.push_back( operationLeft );

		auto rightRight = node->GetLabelRight();
		std::shared_ptr<COperation> operationRight = NEW<COperation>( OT_JNE );
		operationRight->GetJumpPoints().push_back( rightRight );
		code.push_back( operationRight );

		assert( false ); //TODO
	}

	void CCodeGeneratorVisitor::Visit( const IRTree::IRTSSeq * node )
	{
		startMethod();
		visitStatement( node->GetStmLeft() );
		visitStatement( node->GetStmRight() );		
	}

	void CCodeGeneratorVisitor::Visit( const IRTree::IRTSLabel * node )
	{
		startMethod();

		auto label = node->GetLabel();
		std::shared_ptr<CLabelDefinition> labelDefinition = NEW<CLabelDefinition>( label );
		
		code.push_back( labelDefinition );
	}

	void CCodeGeneratorVisitor::Visit( const IRTree::IAccess * node )
	{
		startMethod();
		// ƒолжны найти это при разборе случаев сверху
		assert( false );
	}

	void CCodeGeneratorVisitor::Visit( const IRTree::IRTEConstBool * node )
	{
		startMethod();
		assert( false ); //TODO
	}

	void CCodeGeneratorVisitor::SetFrame( std::shared_ptr<IRTree::CFrame> _frame )
	{
		frame = _frame;
	}

	CSharedPtrVector<IInstruction> CCodeGeneratorVisitor::GetCode() const
	{
		return code;
	}

	void CCodeGeneratorVisitor::startVisit()
	{
		assert( returnValue == 0 );
		assert( frame != 0 );
	}

	void CCodeGeneratorVisitor::startMethod()
	{
		assert( returnValue == 0 );
		assert( frame != 0 );
	}
} // namespace CodeGeneration
