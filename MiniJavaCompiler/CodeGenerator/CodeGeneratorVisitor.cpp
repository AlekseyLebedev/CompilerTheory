#include <cassert>
#include <memory>

#include "CodeGeneratorVisitor.h"

#define NEW std::make_shared
#define DYNAMIC_CAST std::dynamic_pointer_cast

namespace CodeGeneration {

	CCodeGeneratorVisitor::CCodeGeneratorVisitor() : hasCall( false )
	{

	}

	void CCodeGeneratorVisitor::Visit( const IRTree::IRTExpList * node )
	{
		startMethod();
		std::shared_ptr<CMoveOperation> operation = NEW<CMoveOperation>( newTemp(), visitExpression( node->GetHead() ) );
		operation->GetDefinedTemps().push_back( operation->GetTo() );
		callArguments.push_back( operation->GetTo() );
		code.push_back( operation );

		// На самом деле все равно, что положить в returnValue. Это не используется. На всякий случай, поддержал правильную семантику оператора запятая
		returnValue = visitExpression( node->GetTail() );
		if( returnValue == 0 ) {
			returnValue = operation->GetTo();
		}
	}

	void CCodeGeneratorVisitor::Visit( const IRTree::IRTEConst * node )
	{
		startMethod();
		// Должны найти это при разборе случаев сверху
		assert( false );
	}

	void CCodeGeneratorVisitor::Visit( const IRTree::IRTEName * node )
	{
		startMethod();
		// Предположительно сюда не заходим, но это не факт
		assert( false ); //TODO
	}

	void CCodeGeneratorVisitor::Visit( const IRTree::IRTETemp * node )
	{
		startMethod();
		returnValue = node->GetTemp();
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

	static bool applyBoolOperation( IRTree::RELOP operation, bool leftArg, bool rigthArg )
	{
		switch( operation ) {
			case IRTree::BINOP_AND:
				return leftArg && rigthArg;
			case IRTree::BINOP_OR:
				return leftArg || rigthArg;
			case IRTree::BINOP_XOR:
				return leftArg ^ rigthArg;			
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
		std::shared_ptr<IRTree::IConst> leftIConst = std::dynamic_pointer_cast<IRTree::IConst>( left );
		std::shared_ptr<IRTree::IConst> rightIConst = std::dynamic_pointer_cast<IRTree::IConst>( right );
		std::shared_ptr<COperation> operation;
		std::shared_ptr<CTemp> resultTemp;
		resultTemp = newTemp();

		// 1 случай: оба константы
		if( leftIConst && rightIConst ) {
			operation = NEW<COperation>( OT_LoadConst );
			if( opType >= IRTree::BINOP_PLUS && opType <= IRTree::BINOP_MOD ) {
				std::shared_ptr<IRTree::IRTEConst> leftConst = std::dynamic_pointer_cast<IRTree::IRTEConst>( leftIConst );
				std::shared_ptr<IRTree::IRTEConst> rightConst = std::dynamic_pointer_cast<IRTree::IRTEConst>( rightIConst );
				int resultConst = applyIntOperation( opType, leftConst->GetValue(), rightConst->GetValue() );
				operation->GetConstants().push_back( resultConst );
				operation->GetArguments().push_back( resultTemp );
			} else if( opType >= IRTree::BINOP_AND &&  opType <= IRTree::BINOP_XOR ) {
				std::shared_ptr<IRTree::IRTEConstBool> leftConst = std::dynamic_pointer_cast<IRTree::IRTEConstBool>( leftIConst );
				std::shared_ptr<IRTree::IRTEConstBool> rightConst = std::dynamic_pointer_cast<IRTree::IRTEConstBool>( rightIConst );
				int resultConst = applyBoolOperation( opType, leftConst->GetValue(), rightConst->GetValue() );
				operation->GetConstants().push_back( resultConst );
				operation->GetArguments().push_back( resultTemp );
			}				
		}
		// 2 случай: один из аргументов константа, другой - регистр
		else if( ( !leftIConst && rightIConst ) || ( leftIConst && !rightIConst ) ) {			
			
			std::shared_ptr<CTemp> temp;
			std::shared_ptr<CTemp> resultTemp = newTemp();
			int constInt;

			if( !leftIConst ) {
				assert( rightIConst );				
				temp = visitExpression( left );
				std::shared_ptr<IRTree::IRTEConst> rightConst = std::dynamic_pointer_cast<IRTree::IRTEConst>( rightIConst );
				std::shared_ptr<IRTree::IRTEConstBool> rightConstBool;
				if( rightConst ) {
					constInt = rightConst->GetValue();
				} else {
					rightConstBool = std::dynamic_pointer_cast<IRTree::IRTEConstBool>( rightIConst );
					constInt = rightConstBool->GetValue();
				}
				switch( opType ) {
					case IRTree::BINOP_PLUS:
						operation = NEW<COperation>( OT_AddTempConst );
						break;
					case IRTree::BINOP_MINUS:
						operation = NEW<COperation>( OT_SubTempConstRight );
						break;
					case IRTree::BINOP_MUL:
						operation = NEW<COperation>( OT_MulTempConst );
						break;
					case IRTree::BINOP_DIV:
						operation = NEW<COperation>( OT_DivTempConstRight );
						break;
					case IRTree::BINOP_AND:
						operation = NEW<COperation>( OT_AndTempConst );
						break;
					case IRTree::BINOP_OR:
						operation = NEW<COperation>( OT_OrTempConst );
						break;
					case IRTree::BINOP_XOR:
						operation = NEW<COperation>( OT_XorTempConst );
						break;
					default:
						assert( false );
						break;
				}
				operation->GetArguments().push_back( resultTemp );
				operation->GetArguments().push_back( temp );
				operation->GetConstants().push_back( constInt );				
			} else {
				assert( leftIConst );
				temp = visitExpression( right );
				std::shared_ptr<IRTree::IRTEConst> leftConst = std::dynamic_pointer_cast<IRTree::IRTEConst>( leftIConst );
				std::shared_ptr<IRTree::IRTEConstBool> leftConstBool;
				if( leftConst ) {
					constInt = leftConst->GetValue();
				} else {
					leftConstBool = std::dynamic_pointer_cast<IRTree::IRTEConstBool>( rightIConst );
					constInt = leftConstBool->GetValue();
				}
				switch( opType ) {
					case IRTree::BINOP_PLUS:
						operation = NEW<COperation>( OT_AddTempConst );
						break;
					case IRTree::BINOP_MINUS:
						operation = NEW<COperation>( OT_SubTempConstLeft );
						break;
					case IRTree::BINOP_MUL:
						operation = NEW<COperation>( OT_MulTempConst );
						break;
					case IRTree::BINOP_DIV:
						operation = NEW<COperation>( OT_DivTempConstLeft );
						break;
					case IRTree::BINOP_AND:
						operation = NEW<COperation>( OT_AndTempConst );
						break;
					case IRTree::BINOP_OR:
						operation = NEW<COperation>( OT_OrTempConst );
						break;
					case IRTree::BINOP_XOR:
						operation = NEW<COperation>( OT_XorTempConst );
						break;
					default:
						assert( false );
						break;
				}
				operation->GetArguments().push_back( resultTemp );
				operation->GetArguments().push_back( temp );
				operation->GetConstants().push_back( constInt );				
			}		
		}
		// 3 случай: оба регистры
		else {
			assert( !rightIConst );
			assert( !leftIConst );
			std::shared_ptr<CTemp> tempLeft = visitExpression( left );
			std::shared_ptr<CTemp> tempRight = visitExpression( right );

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
				case IRTree::BINOP_AND:
					operation = NEW<COperation>( OT_AndTemps );
					break;
				case IRTree::BINOP_OR:
					operation = NEW<COperation>( OT_OrTemps );
					break;
				case IRTree::BINOP_XOR:
					operation = NEW<COperation>( OT_XorTemps );
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
		assert( callArguments.size() == 0 );

		visitExpression( node->GetArgs() );

		std::shared_ptr<IRTree::IRTEName> name = DYNAMIC_CAST<IRTree::IRTEName>( node->GetFunc() );
		assert( name != 0 );

		std::shared_ptr<CCallOperation> operation = NEW<CCallOperation>( name->GetLabel() );
		returnValue = newTemp();
		operation->GetDefinedTemps().push_back( returnValue );
		operation->GetArguments().push_back( returnValue );

		visitExpression( node->GetArgs() );
		for( size_t i = 0; i < callArguments.size(); i++ ) {
			operation->GetArguments().push_back( callArguments[i] );
		}
		code.push_back( operation );

		callArguments.clear();
		hasCall = true;
	}

	void CCodeGeneratorVisitor::Visit( const IRTree::IRTEEseq * node )
	{
		startMethod();
		// Этих узлов быть не должно
		assert( false );
	}

	void CCodeGeneratorVisitor::Visit( const IRTree::IRTSMove * node )
	{
		startMethod();
		std::shared_ptr<IRTree::IRTExpression> dist =  node->GetExrDst();
		std::shared_ptr<IRTree::IRTExpression> source = node->GetExrSrc();
		std::shared_ptr<IRTree::IRTEMem> distMem = std::dynamic_pointer_cast<IRTree::IRTEMem>(dist);
		std::shared_ptr<IRTree::IRTEMem> sourceMem = std::dynamic_pointer_cast<IRTree::IRTEMem>(source);
		std::shared_ptr<COperation> operation;
		if( sourceMem && distMem ) {
			operation = NEW<COperation>( OT_Movem );
			std::shared_ptr<CTemp> distTemp  = visitExpression( distMem->GetExp() );
			std::shared_ptr<CTemp> sourceTemp = visitExpression( sourceMem->GetExp() );
			operation->GetArguments().push_back( distTemp );
			operation->GetArguments().push_back( sourceTemp );
		} else if( distMem ) {
			std::shared_ptr<IRTree::IRTExpression> distExp = distMem->GetExp();
			std::shared_ptr<IRTree::IRTEBinop> distExpBinop = std::dynamic_pointer_cast<IRTree::IRTEBinop>(distExp);
			std::shared_ptr<IRTree::IRTEConst> distExpConst = std::dynamic_pointer_cast<IRTree::IRTEConst>(distExp);
			if( distExpBinop ) {
				if( distExpBinop->GetBinop() == IRTree::BINOP_PLUS ) {
					std::shared_ptr<IRTree::IRTExpression> binopLeft = distExpBinop->GetLeft();
					std::shared_ptr<IRTree::IRTExpression> binopRight = distExpBinop->GetRight();
					std::shared_ptr<IRTree::IRTEConst> binopLeftConst = std::dynamic_pointer_cast<IRTree::IRTEConst>(binopLeft);
					std::shared_ptr<IRTree::IRTEConst> binopRightConst = std::dynamic_pointer_cast<IRTree::IRTEConst>(binopRight);
					if( binopLeftConst ) {
						assert( !binopRightConst );
						operation = NEW<COperation>( OT_Store );
						operation->GetArguments().push_back( visitExpression( binopRight ) );
						operation->GetConstants().push_back( binopLeftConst->GetValue() );
					} else if( binopRightConst ) {
						assert( !binopLeftConst );
						operation = NEW<COperation>( OT_Store );
						operation->GetArguments().push_back( visitExpression( binopLeft ) );
						operation->GetConstants().push_back( binopRightConst->GetValue() );
					} else {
						assert( false );
					}
				} else  if ( distExpConst ) {
					operation = NEW<COperation>( OT_StoreConst );
					operation->GetConstants().push_back( distExpConst->GetValue() );
				} else {
					operation = NEW<COperation>( OT_StoreTemp );
					operation->GetArguments().push_back( visitExpression( distExp ) );
				}
			}
			operation->GetArguments().push_back( visitExpression( source ) );
		}		
		assert( operation ); 
		code.push_back( operation );
	}

	void CCodeGeneratorVisitor::Visit( const IRTree::IRTSExp * node )
	{
		startMethod();
		// Тут нужно что-то делать только если внутри Call (оптимизация)
		// TODO: а вдруг я не прав? Вроде бы ничего другого не могло вызвать побочных эффектов
		int codeSize = code.size();
		hasCall = false;
		visitExpression( node->GetExp() );
		if( !hasCall ) {
			// Оптимизаяци: удаляем лишнее, если не было Call внутри.
			code.erase( code.begin() + codeSize, code.end() );
		}
		hasCall = false;
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

		auto relop = node->GetRelop();

		auto expLeft = node->GetExpLeft();
		auto expRight = node->GetExpRight();
		std::shared_ptr<IRTree::IConst> leftConst = std::dynamic_pointer_cast<IRTree::IConst>( expLeft );
		std::shared_ptr<IRTree::IConst> rightConst = std::dynamic_pointer_cast<IRTree::IConst>( expRight );

		// если оба константы 
		if( leftConst && rightConst ) {

		} // если 
		else if( (!leftConst && rightConst) || (leftConst && !rightConst) ) {

		} else {

		}
		std::shared_ptr<COperation> operation = NEW<COperation>( OT_CMP );
		if( std::dynamic_pointer_cast<IRTree::IRTEConst>( expLeft ) ) {

		} else {
			operation->GetArguments().push_back( visitExpression( expLeft ) );
		}

		if( std::dynamic_pointer_cast<IRTree::IRTEConst>( expRight ) ) {

		} else {
			operation->GetArguments().push_back( visitExpression( expRight ) );
		}

		auto labelLeft = node->GetLabelLeft();
		auto rightRight = node->GetLabelRight();
		std::shared_ptr<COperation> operationLeft;
		std::shared_ptr<COperation> operationRight;

		switch( relop ) {
			case IRTree::CJUMP_EQ:
				operationLeft = NEW<COperation>( OT_JE );
				operationRight = NEW<COperation>( OT_JNE );
				break;
			case IRTree::CJUMP_NE:
				operationLeft = NEW<COperation>( OT_JNE );
				operationRight = NEW<COperation>( OT_JE );
				break;
			case IRTree::CJUMP_LT:
				operationLeft = NEW<COperation>( OT_JL );
				operationRight = NEW<COperation>( OT_JGE );
				break;
			case IRTree::CJUMP_LE:
				operationLeft = NEW<COperation>( OT_JLE );
				operationRight = NEW<COperation>( OT_JG );
				break;
			case IRTree::CJUMP_GE:
				operationLeft = NEW<COperation>( OT_JGE );
				operationRight = NEW<COperation>( OT_JL );
				break;
			case IRTree::CJUMP_GT:
				operationLeft = NEW<COperation>( OT_JG );
				operationRight = NEW<COperation>( OT_JLE );
				break;
			default:
				assert( false );
				break;
		}

		operationLeft->GetJumpPoints().push_back( labelLeft );
		operationRight->GetJumpPoints().push_back( rightRight );
		code.push_back( operation );
		code.push_back( operationLeft );
		code.push_back( operationRight );
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
		// Должны найти это при разборе случаев сверху
		assert( false );
	}

	void CCodeGeneratorVisitor::Visit( const IRTree::IRTEConstBool * node )
	{
		startMethod();
		// Должны найти это при разборе случаев сверху
		assert( false );
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
