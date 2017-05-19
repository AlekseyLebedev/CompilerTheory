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
		std::shared_ptr<IRTree::IConst> constExpr = DYNAMIC_CAST<IRTree::IConst>( node->GetHead() );
		std::shared_ptr<CTemp> resultTemp = newTemp();
		if( constExpr != 0 ) {
			std::shared_ptr<COperation> operation = NEW<COperation>( OT_LoadConst );
			operation->GetDefinedTemps().push_back( resultTemp );
			operation->GetArguments().push_back( resultTemp );
			operation->GetConstants().push_back( constExpr->GetValueAsInt() );
			code.push_back( operation );
		} else {
			std::shared_ptr<IRTree::IRTETemp> tempArg = DYNAMIC_CAST<IRTree::IRTETemp>( node->GetHead() );
			if( tempArg != 0 ) {
				resultTemp = tempArg->GetTemp();
			} else {
				resultTemp = visitExpression( node->GetHead() );
			}
		}
		callArguments.push_back( resultTemp );

		// Ќа самом деле все равно, что положить в returnValue. Ёто не используетс€. Ќа вс€кий случай, поддержал правильную семантику оператора зап€та€
		returnValue = visitExpression( node->GetTail() );
		if( returnValue == 0 ) {
			returnValue = resultTemp;
		}
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
		// ѕредположительно сюда не заходим, но это не факт
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
		std::shared_ptr<IRTree::IConst> leftIConst = DYNAMIC_CAST<IRTree::IConst>( left );
		std::shared_ptr<IRTree::IConst> rightIConst = DYNAMIC_CAST<IRTree::IConst>( right );
		std::shared_ptr<COperation> operation;
		std::shared_ptr<CTemp> resultTemp;
		resultTemp = newTemp();

		// 1 случай: оба константы
		if( leftIConst && rightIConst ) {
			operation = NEW<COperation>( OT_LoadConst );
			if( opType >= IRTree::BINOP_PLUS && opType <= IRTree::BINOP_MOD ) {
				std::shared_ptr<IRTree::IRTEConst> leftConst = DYNAMIC_CAST<IRTree::IRTEConst>( leftIConst );
				std::shared_ptr<IRTree::IRTEConst> rightConst = DYNAMIC_CAST<IRTree::IRTEConst>( rightIConst );
				int resultConst = applyIntOperation( opType, leftConst->GetValue(), rightConst->GetValue() );
				operation->GetConstants().push_back( resultConst );
				operation->GetArguments().push_back( resultTemp );
			} else if( opType >= IRTree::BINOP_AND &&  opType <= IRTree::BINOP_XOR ) {
				std::shared_ptr<IRTree::IRTEConstBool> leftConst = DYNAMIC_CAST<IRTree::IRTEConstBool>( leftIConst );
				std::shared_ptr<IRTree::IRTEConstBool> rightConst = DYNAMIC_CAST<IRTree::IRTEConstBool>( rightIConst );
				int resultConst = applyBoolOperation( opType, leftConst->GetValue(), rightConst->GetValue() );
				operation->GetConstants().push_back( resultConst );
				operation->GetArguments().push_back( resultTemp );
			}
		}
		// 2 случай: один из аргументов константа, другой - регистр
		else if( (!leftIConst && rightIConst) || (leftIConst && !rightIConst) ) {

			std::shared_ptr<CTemp> temp;
			//std::shared_ptr<CTemp> resultTemp = newTemp();
			int constInt;

			if( !leftIConst ) {
				assert( rightIConst );
				temp = visitExpression( left );
				std::shared_ptr<IRTree::IRTEConst> rightConst = DYNAMIC_CAST<IRTree::IRTEConst>( rightIConst );
				std::shared_ptr<IRTree::IRTEConstBool> rightConstBool;
				if( rightConst ) {
					constInt = rightConst->GetValue();
				} else {
					rightConstBool = DYNAMIC_CAST<IRTree::IRTEConstBool>( rightIConst );
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
				std::shared_ptr<IRTree::IRTEConst> leftConst = DYNAMIC_CAST<IRTree::IRTEConst>( leftIConst );
				std::shared_ptr<IRTree::IRTEConstBool> leftConstBool;
				if( leftConst ) {
					constInt = leftConst->GetValue();
				} else {
					leftConstBool = DYNAMIC_CAST<IRTree::IRTEConstBool>( rightIConst );
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
					assert( binop->GetBinop() == IRTree::BINOP_PLUS );
					std::shared_ptr<COperation> operation = NEW<COperation>( OT_MemFramePointerPlusConst );
					returnValue = newTemp();
					operation->GetDefinedTemps().push_back( returnValue );
					operation->GetArguments().push_back( returnValue );
					operation->GetConstants().push_back( rightConst->GetValue() );
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

		std::shared_ptr<IRTree::IRTEName> name = DYNAMIC_CAST<IRTree::IRTEName>( node->GetFunc() );
		assert( name != 0 );

		visitExpression( node->GetArgs() );

		std::shared_ptr<CCallOperation> operation = NEW<CCallOperation>( name->GetLabel() );
		returnValue = newTemp();
		operation->GetDefinedTemps().push_back( returnValue );
		operation->GetArguments().push_back( returnValue );

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
		// Ётих узлов быть не должно
		assert( false );
	}

	void CCodeGeneratorVisitor::Visit( const IRTree::IRTSMove * node )
	{
		startMethod();
		std::shared_ptr<IRTree::IRTExpression> dist = node->GetExrDst();
		std::shared_ptr<IRTree::IRTExpression> source = node->GetExrSrc();
		std::shared_ptr<IRTree::IRTEMem> distMem = DYNAMIC_CAST<IRTree::IRTEMem>( dist );
		std::shared_ptr<IRTree::IRTEMem> sourceMem = DYNAMIC_CAST<IRTree::IRTEMem>( source );
		std::shared_ptr<COperation> operation;
		if( sourceMem && distMem ) {
			std::shared_ptr<IRTree::IRTEBinop> destMemBinop = DYNAMIC_CAST<IRTree::IRTEBinop>( distMem->GetExp() );
			if( destMemBinop && (DYNAMIC_CAST<IRTree::IAccess>( destMemBinop->GetLeft() ) != 0) ) {
				assert( destMemBinop->GetBinop() == IRTree::BINOP_PLUS );
				std::shared_ptr<IRTree::IRTEConst> memConst = DYNAMIC_CAST<IRTree::IRTEConst>( destMemBinop->GetRight() );
				assert( memConst != 0 );
				operation = NEW<COperation>( OT_MoveMemToFramePointerPlusConst );
				std::shared_ptr<IRTree::IRTEBinop> sourceBinop = DYNAMIC_CAST<IRTree::IRTEBinop>( sourceMem->GetExp() );
				if( sourceBinop ) {
					std::shared_ptr<IRTree::IAccess> sourceBinopAccess = DYNAMIC_CAST<IRTree::IAccess>( sourceBinop->GetLeft() );
					std::shared_ptr<IRTree::IConst> sourceBinopConst = DYNAMIC_CAST<IRTree::IConst>( sourceBinop->GetRight() );
					assert( sourceBinopAccess != 0 );
					assert( sourceBinopConst != 0 );
					assert( sourceBinopAccess->GetName() == IRTree::CFrame::FramePointerName );
					std::shared_ptr<COperation> loadOperation = NEW<COperation>(OT_MemFramePointerPlusConst);
					std::shared_ptr<CTemp> temp = newTemp();
					loadOperation->GetArguments().push_back( temp );
					loadOperation->GetDefinedTemps().push_back(temp);
					loadOperation->GetConstants().push_back( sourceBinopConst->GetValueAsInt() );
				} else {
					std::shared_ptr<CTemp> sourceTemp = visitExpression( sourceMem->GetExp() );
					operation->GetArguments().push_back( sourceTemp );
				}
				operation->GetConstants().push_back( memConst->GetValue() );
			} else {
				std::shared_ptr<IRTree::IAccess> destAccess = DYNAMIC_CAST<IRTree::IAccess>( distMem->GetExp() );
				if( destAccess ) {
					assert( destAccess->GetName() == IRTree::CFrame::ReturnName );
					std::shared_ptr<IRTree::IRTEBinop> sourceBinop = DYNAMIC_CAST<IRTree::IRTEBinop>( sourceMem->GetExp() );
					if( sourceBinop && (DYNAMIC_CAST<IRTree::IAccess>( sourceBinop->GetLeft() ) != 0) ) {
						std::shared_ptr<IRTree::IAccess> access = DYNAMIC_CAST<IRTree::IAccess>( sourceBinop->GetLeft() );
						assert( access->GetName() == IRTree::CFrame::FramePointerName );
						std::shared_ptr<IRTree::IRTEConst> constExpr = DYNAMIC_CAST<IRTree::IRTEConst>( sourceBinop->GetRight() );
						assert( constExpr != 0 );
						assert( sourceBinop->GetBinop() == IRTree::BINOP_PLUS );

						operation = NEW<COperation>( OT_MoveFramePointerPlusConstToEax );
						operation->GetConstants().push_back( constExpr->GetValue() );
					} else {
						operation = NEW<COperation>( OT_MoveMemToEax );
						std::shared_ptr<CTemp> sourceTemp = visitExpression( sourceMem->GetExp() );
						operation->GetArguments().push_back( sourceTemp );
					}
				} else {
					std::shared_ptr<IRTree::IRTEBinop> sourcebinop = DYNAMIC_CAST<IRTree::IRTEBinop>( sourceMem->GetExp() );
					std::shared_ptr<CTemp> distTemp = visitExpression( distMem->GetExp() );
					if( sourcebinop != 0 ) {
						operation = NEW<COperation>( OT_MoveFramePointerPlusConstToMem );
						operation->GetArguments().push_back( distTemp );
						assert( sourcebinop->GetBinop() == IRTree::BINOP_PLUS );
						assert( DYNAMIC_CAST<IRTree::IAccess>( sourcebinop->GetLeft() ) != 0 );
						assert( DYNAMIC_CAST<IRTree::IAccess>( sourcebinop->GetLeft() )->GetName() == IRTree::CFrame::FramePointerName );
						std::shared_ptr<IRTree::IRTEConst> rightconst = DYNAMIC_CAST<IRTree::IRTEConst>( sourcebinop->GetRight() );
						assert( rightconst != 0 );
						operation->GetConstants().push_back( rightconst->GetValueAsInt() );
					} else {
						operation = NEW<COperation>( OT_Movem );
						std::shared_ptr<CTemp> sourceTemp = visitExpression( sourceMem->GetExp() );
						operation->GetArguments().push_back( distTemp );
						operation->GetArguments().push_back( sourceTemp );
					}
				}
			}
		} else if( distMem ) {
			std::shared_ptr<IRTree::IRTExpression> distExp = distMem->GetExp();
			std::shared_ptr<IRTree::IRTEBinop> distExpBinop = DYNAMIC_CAST<IRTree::IRTEBinop>( distExp );
			std::shared_ptr<IRTree::IRTEConst> distExpConst = DYNAMIC_CAST<IRTree::IRTEConst>( distExp );
			if( distExpBinop ) {
				if( distExpBinop->GetBinop() == IRTree::BINOP_PLUS ) {
					std::shared_ptr<IRTree::IRTExpression> binopLeft = distExpBinop->GetLeft();
					std::shared_ptr<IRTree::IRTExpression> binopRight = distExpBinop->GetRight();
					std::shared_ptr<IRTree::IRTEConst> binopLeftConst = DYNAMIC_CAST<IRTree::IRTEConst>( binopLeft );
					std::shared_ptr<IRTree::IRTEConst> binopRightConst = DYNAMIC_CAST<IRTree::IRTEConst>( binopRight );
					if( binopLeftConst ) {
						assert( !binopRightConst );
						operation = NEW<COperation>( OT_Store );
						operation->GetArguments().push_back( visitExpression( binopRight ) );
						operation->GetConstants().push_back( binopLeftConst->GetValue() );
					} else if( binopRightConst ) {
						assert( !binopLeftConst );
						std::shared_ptr<IRTree::IAccess> leftAccess = DYNAMIC_CAST<IRTree::IAccess>( binopLeft );
						if( leftAccess != 0 ) {
							operation = NEW<COperation>( OT_StoreToFramePointerPlusConst );
							operation->GetConstants().push_back( binopRightConst->GetValue() );
						} else {
							operation = NEW<COperation>( OT_Store );
							operation->GetArguments().push_back( visitExpression( binopLeft ) );
							operation->GetConstants().push_back( binopRightConst->GetValue() );
						}
					} else {
						assert( false );
					}
				} else  if( distExpConst ) {
					assert( false ); // TODO: очень странно записывать что-то в константу
					operation = NEW<COperation>( OT_StoreConst );
					operation->GetConstants().push_back( distExpConst->GetValue() );
				} else {
					operation = NEW<COperation>( OT_StoreTemp );
					operation->GetArguments().push_back( visitExpression( distExp ) );
				}
			} else {
				std::shared_ptr<IRTree::IAccess> destAccess = DYNAMIC_CAST<IRTree::IAccess>( distMem->GetExp() );
				if( destAccess ) {
					assert( destAccess->GetName() == IRTree::CFrame::ReturnName );
					operation = NEW<COperation>( OT_MoveTempToEax );
				} else {
					assert( false );
				}
			}
			assert( operation != 0 );
			std::shared_ptr<IRTree::IConst> constExpr = DYNAMIC_CAST<IRTree::IConst>( source );
			if( constExpr != 0 ) {
				// TODO: костыль, нужно переделать
				std::shared_ptr<COperation> kostyl = NEW<COperation>( OT_LoadConst );
				kostyl->GetArguments().push_back( newTemp() );
				kostyl->GetDefinedTemps().push_back( kostyl->GetArguments()[0] );
				kostyl->GetConstants().push_back( constExpr->GetValueAsInt() );
				code.push_back( kostyl );
				operation->GetArguments().push_back( kostyl->GetArguments()[0] );
			} else {
				operation->GetArguments().push_back( visitExpression( source ) );
			}
		} else {
			std::shared_ptr<IRTree::IRTETemp> dstTemp = DYNAMIC_CAST<IRTree::IRTETemp>( dist );
			std::shared_ptr<IRTree::IRTETemp> sourceTemp = DYNAMIC_CAST<IRTree::IRTETemp>( source );
			if( dstTemp ) {
				std::shared_ptr<CTemp> temp = dstTemp->GetTemp();
				operation = NEW<COperation>( OT_LoadTemp );
				operation->GetArguments().push_back( temp );
				operation->GetArguments().push_back( visitExpression( source ) );
			} else if( sourceTemp ) {
				std::shared_ptr<CTemp> temp = sourceTemp->GetTemp();
				operation = NEW<COperation>( OT_StoreTemps );
				operation->GetArguments().push_back( temp );
				operation->GetArguments().push_back( visitExpression( dist ) );
			}
		}
		assert( operation );
		code.push_back( operation );
	}

	void CCodeGeneratorVisitor::Visit( const IRTree::IRTSExp * node )
	{
		startMethod();
		// “ут нужно что-то делать только если внутри Call (оптимизаци€)
		// TODO: а вдруг € не прав? ¬роде бы ничего другого не могло вызвать побочных эффектов
		int codeSize = code.size();
		hasCall = false;
		visitExpression( node->GetExp() );
		if( !hasCall ) {
			// ќптимиза€ци: удал€ем лишнее, если не было Call внутри.
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

	static IRTree::RELOP exchangeOperator( IRTree::RELOP operation )
	{
		switch( operation ) {
			case IRTree::CJUMP_EQ:
				return IRTree::CJUMP_NE;
			case IRTree::CJUMP_NE:
				return IRTree::CJUMP_EQ;
			case IRTree::CJUMP_LT:
				return IRTree::CJUMP_GE;
			case IRTree::CJUMP_GT:
				return IRTree::CJUMP_LE;
			case IRTree::CJUMP_LE:
				return IRTree::CJUMP_GT;
			case IRTree::CJUMP_GE:
				return IRTree::CJUMP_LT;
			default:
				assert( false );
				break;
		}
	}

	void CCodeGeneratorVisitor::Visit( const IRTree::IRTSCjump * node )
	{
		startMethod();

		auto relop = node->GetRelop();

		auto expLeft = node->GetExpLeft();
		auto expRight = node->GetExpRight();
		std::shared_ptr<IRTree::IConst> leftIConst = DYNAMIC_CAST<IRTree::IConst>( expLeft );
		std::shared_ptr<IRTree::IConst> rightIConst = DYNAMIC_CAST<IRTree::IConst>( expRight );

		// если оба константы 
		if( leftIConst && rightIConst ) {
			std::shared_ptr<IRTree::IRTEConst> leftConst = DYNAMIC_CAST<IRTree::IRTEConst>( leftIConst );
			std::shared_ptr<IRTree::IRTEConst> rightConst = DYNAMIC_CAST<IRTree::IRTEConst>( rightIConst );
			int left = leftConst->GetValueAsInt();
			int right = rightConst->GetValueAsInt();
			bool logicResult;

			switch( relop ) {
				case IRTree::CJUMP_EQ:
					logicResult = (left == right);
					break;
				case IRTree::CJUMP_NE:
					logicResult = (left != right);
					break;
				case IRTree::CJUMP_LT:
					logicResult = (left < right);
					break;
				case IRTree::CJUMP_GT:
					logicResult = (left > right);
					break;
				case IRTree::CJUMP_LE:
					logicResult = (left <= right);
					break;
				case IRTree::CJUMP_GE:
					logicResult = (left >= right);
					break;
			}

			auto labelLeft = node->GetLabelLeft();
			auto rightRight = node->GetLabelRight();

			std::shared_ptr<COperation> operation = NEW<COperation>( OT_JMP );
			if( logicResult ) {
				operation->GetJumpPoints().push_back( labelLeft );
			} else {
				operation->GetJumpPoints().push_back( rightRight );
			}
			code.push_back( operation );
			return;

		} // если одна константа // считаем что всегда константа справа типа сравнение if( a < 5 )
		else if( (!leftIConst && rightIConst) || (leftIConst && !rightIConst) ) {
			// теперь константа всегда справа
			if( leftIConst && !rightIConst ) {
				std::swap( leftIConst, rightIConst );
				relop = exchangeOperator( relop );
			}
			std::shared_ptr<COperation> operation = NEW<COperation>( OT_CMPC );
			operation->GetArguments().push_back( visitExpression( expLeft ) );
			std::shared_ptr<IRTree::IRTEConst> rightConst = DYNAMIC_CAST<IRTree::IRTEConst>( rightIConst );
			operation->GetConstants().push_back( rightConst->GetValueAsInt() );
			code.push_back( operation );

		} // если нет констант
		else {
			std::shared_ptr<COperation> operation = NEW<COperation>( OT_CMP );
			operation->GetArguments().push_back( visitExpression( expLeft ) );
			operation->GetArguments().push_back( visitExpression( expRight ) );
			code.push_back( operation );
		}

		auto labelLeft = node->GetLabelLeft();
		std::shared_ptr<COperation> operationLeft;

		switch( relop ) {
			case IRTree::CJUMP_EQ:
				operationLeft = NEW<COperation>( OT_JE );
				break;
			case IRTree::CJUMP_NE:
				operationLeft = NEW<COperation>( OT_JNE );
				break;
			case IRTree::CJUMP_LT:
				operationLeft = NEW<COperation>( OT_JL );
				break;
			case IRTree::CJUMP_LE:
				operationLeft = NEW<COperation>( OT_JLE );
				break;
			case IRTree::CJUMP_GE:
				operationLeft = NEW<COperation>( OT_JGE );
				break;
			case IRTree::CJUMP_GT:
				operationLeft = NEW<COperation>( OT_JG );
				break;
			default:
				assert( false );
				break;
		}

		operationLeft->GetJumpPoints().push_back( labelLeft );
		code.push_back( operationLeft );
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
		// ƒолжны найти это при разборе случаев сверху
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
