#include <cassert>
#include <stack>
#include <map>

#include "IRTBuilderVisitor.h"
#include "IRTExpConverter.h"
#include "..\SymbolTable\ClassInfo.h"
#include "..\AbstractTreeGenerator\Type.h"

using TStdType = AbstractTreeGenerator::TStandardType;

namespace IRTree {
	// TODO указатель на CTable
	IRTBuilderVisitor::IRTBuilderVisitor( const SymbolTable::CTable * _table ) : table( _table )
	{
		returnedExpression = 0;
		returnedStatement = 0;
		codeFragment = 0;
		startPoint = 0;
		currentFrame = 0;
		currentClass = TStdType::ST_Void;
		returnValueType = TStdType::ST_Void;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CArgument* const argument )
	{
		int name = argument->GetIdExpression()->GetName();
		int type = argument->GetType()->GetType();
		currentFrame->InsertVariable( name, std::make_shared<IAccess>( name, type ) );
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CArgumentList* const arguments )
	{
		visitChild( arguments->GetArgument().get() );
		visitChild( arguments->GetArgumentList().get() );
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CAssignmentListStatement* const statement )
	{
		std::shared_ptr<IRTExpression> src = visitChild( statement->GetExpressionSecond().get() );
		std::shared_ptr<IRTExpression> id = visitChild( statement->GetIdExpression().get() );
		int returnType = returnValueType;
		std::shared_ptr<IRTExpression> ptr = visitChild( statement->GetExpressionFirst().get() );

		int typesize;
		if( returnType > 0 ) {
			typesize = table->GetClassInfo( returnType, statement->GetIdExpression().get() ).GetSize( table );
		} else {
			typesize = SymbolTable::CClassInfo::getSizeOfType( returnType, table );
		}
		std::shared_ptr<IRTSMove> root = std::make_shared<IRTSMove>( std::make_shared<IRTEBinop>(
			RELOP::BINOP_PLUS, id, std::make_shared<IRTEBinop>(
				RELOP::BINOP_MUL, ptr, std::make_shared<IRTEConst>( typesize ) )
			), src );
		returnedStatement = root;
		returnValueType = TStdType::ST_Void;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CAssignmentStatement* const statement )
	{
		statement->GetIdExpression();
		statement->GetExpression();
		std::shared_ptr<IRTExpression> src = visitChild( statement->GetExpression().get() );
		std::shared_ptr<IRTExpression> dst = visitChild( statement->GetIdExpression().get() );

		std::shared_ptr<IRTSMove> root = std::make_shared<IRTSMove>( dst, src );
		returnedStatement = root;
		returnValueType = TStdType::ST_Void;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CClassDeclaration* const classdeclaration )
	{
		currentClass = classdeclaration->GetIdExpression()->GetName();
		visitChild( classdeclaration->GetMethodDeclarationList().get() );
		returnValueType = TStdType::ST_Void;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CClassDeclarationList* const classlist )
	{
		visitChild( classlist->GetClassDeclaration().get() );
		visitChild( classlist->GetClassDeclarationList().get() );
		returnValueType = TStdType::ST_Void;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CClassExtend* const )
	{
		// Не вызывается
		assert( false );
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CCompoundStatement* const statement )
	{
		visitChild( statement->GetStatementList().get() );
		returnValueType = TStdType::ST_Void;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CConstructorExpression* const expression )
	{

		assert( false ); // TODO
		//ctor
		returnedExpression = std::make_shared<IRTECall>( std::make_shared<IRTEName>( table->GetAllocLabel() ), std::make_shared<IRTExpList>( std::make_shared<IRTEConst>(
			table->GetClassInfo( expression->GetIdExpression()->GetName() ).GetSize( table ) ), nullptr ) );
		returnValueType = expression->GetIdExpression()->GetName();
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CExpressionList* const expList )
	{
		std::shared_ptr<AbstractTreeGenerator::IExpression> head = expList->GetExpression();
		std::shared_ptr<AbstractTreeGenerator::CExpressionList> tail = expList->GetExpressionList();

		std::shared_ptr<IRTExpression> headNode = visitChild( head.get() );
		std::shared_ptr<IRTExpression> root;

		if( tail != nullptr ) {
			tail->Accept( this );

			std::shared_ptr<IRTExpression> tailNode = returnedExpression;
			root = std::make_shared< IRTEEseq>( std::make_shared<IRTSExp>( headNode ), tailNode );
		} else {
			root = std::make_shared< IRTEEseq>( std::make_shared <IRTSExp>( headNode ), nullptr );
		}

		returnedExpression = root;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CIdExpression* const expression )
	{
		std::shared_ptr<IAccess> access = currentFrame->GetDataInfo( expression->GetName() );
		std::shared_ptr<IRTEMem> root = std::make_shared<IRTEMem>( access );
		returnedExpression = root;
		returnValueType = access->GetType();
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CIndexExpression* const indexExp )
	{
		std::shared_ptr<IRTExpression> ptr = visitChild( indexExp->GetExpressionSecond().get() );
		int returnType = returnValueType;
		assert( returnType == TStdType::ST_Int );
		std::shared_ptr<IRTExpression> id = visitChild( indexExp->GetExpressionFirst().get() );
		returnType = returnValueType;

		int typesize;
		if( returnType > 0 ) {
			typesize = table->GetClassInfo( returnType, indexExp->GetExpressionFirst().get() ).GetSize( table );
		} else {
			typesize = SymbolTable::CClassInfo::getSizeOfType( returnType, table );
		}
		std::shared_ptr<IRTEBinop> root = std::make_shared<IRTEBinop>(
			RELOP::BINOP_PLUS, id, std::make_shared<IRTEBinop>( RELOP::BINOP_MUL, ptr, std::make_shared<IRTEConst>( typesize ) ) );
		returnedExpression = root;
		returnValueType = returnType;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CLastExpressionList * const )
	{
		assert( false ); // There is no case
		returnValueType = TStdType::ST_Void;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CLengthExpression* const )
	{
		// call something called length
		assert( false ); // TODO
		returnValueType = TStdType::ST_Int;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CListConstructorExpression* const expression )
	{
		/*std::shared_ptr<IRTECall> root = std::make_shared<IRTECall>( nullptr, nullptr );
		returnedExpression = root;*/
		assert( false ); // TODO
		returnValueType = TStdType::ST_Intlist;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CMainClass* const mainclass )
	{
		currentClass = mainclass->GetClassName()->GetName();
		startPoint = std::make_shared<CCodeFragment>( visitChild( mainclass->GetStatement().get() ) );
		codeFragment = startPoint;
		returnValueType = TStdType::ST_Void;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CMethodDeclaration* const method )
	{
		// what about type of method

		std::shared_ptr<Label> label = table->GetClassInfo( currentClass ).GetMethodInfo( method->GetIdExpression()->GetName() ).GetLabel();
		currentFrame = std::make_shared<CFrame>( currentClass, label );
		returnValueType = TStdType::ST_Void;
		visitChild( method->GetArgumentList().get() );
		visitChild( method->GetVarDeclarationList().get() );
		visitChild( method->GetStatementList() );
		std::shared_ptr<CCodeFragment> bufferFragment = std::make_shared<CCodeFragment>( returnedStatement );
		codeFragment->SetNext( bufferFragment );
		codeFragment = bufferFragment;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CMethodDeclarationList* const methodList )
	{
		visitChild( methodList->GetMethodDeclaration().get() );
		assert( returnValueType == TStdType::ST_Void );
		visitChild( methodList->GetMethodDeclarationList().get() );
		assert( returnValueType == TStdType::ST_Void );
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CNegationExpression* const negExp )
	{
		std::shared_ptr<AbstractTreeGenerator::IExpression> exp = negExp->GetExpression();

		std::shared_ptr<IRTExpression> expNode = visitChild( exp.get() );

		std::shared_ptr<IRTStatement> root = std::make_shared<IRTSExp>( expNode );

		assert( returnValueType == TStdType::ST_Int );
		returnedStatement = root;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CNumberExpr* const numerExp )
	{
		std::shared_ptr<IRTEConst> root = std::make_shared<IRTEConst>( numerExp->GetValue() );
		returnValueType = AbstractTreeGenerator::TStandardType::ST_Int;
		returnedExpression = root;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::COperationExpression* const operExp )
	{
		typedef AbstractTreeGenerator::COperationExpression::TOperationType operationType;
		std::shared_ptr<AbstractTreeGenerator::IExpression> left = operExp->GetLeftOperand();
		operationType operType = operExp->GetOperationType();
		std::shared_ptr<AbstractTreeGenerator::IExpression> right = operExp->GetRightOperand();

		// operType ...

		std::shared_ptr<IRTExpression> leftNode = visitChild( left.get() );
		int leftType = returnValueType;
		std::shared_ptr<IRTExpression> rightNode = visitChild( right.get() );


		assert( leftType == returnValueType );
		assert( returnValueType == TStdType::ST_Int || returnValueType == TStdType::ST_Bool );
		// returnValueType same
		RELOP IRToperationType;
		switch( operType ) {
			case operationType::Plus:
				IRToperationType = BINOP_PLUS;
				break;
			case operationType::Minus:
				IRToperationType = BINOP_MINUS;
				break;
			case operationType::Times:
				IRToperationType = BINOP_MUL;
				break;
			case operationType::Divide:
				IRToperationType = BINOP_DIV;
				break;
			case operationType::And:
				IRToperationType = BINOP_AND;
				break;
			case operationType::Less:
				IRToperationType = CJUMP_LT;
				break;
			case operationType::Mod:
				IRToperationType = BINOP_MOD;
				break;
			case operationType::Or:
				IRToperationType = BINOP_OR;
				break;
			default:
				assert( false );
		}
		std::shared_ptr<IRTEBinop> root = std::make_shared<IRTEBinop>( IRToperationType, leftNode, rightNode );

		returnedExpression = root;
		// ...
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CParenExpression* const parenExpression )
	{
		std::shared_ptr<AbstractTreeGenerator::IExpression> exp = parenExpression->GetExpression();

		std::shared_ptr<IRTExpression> expNode = visitChild( exp.get() );

		std::shared_ptr<IRTExpression> root = expNode;

		returnedExpression = root;
		// returnValueType same
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CPreconditionStatement* const precondStm )
	{
		std::shared_ptr<AbstractTreeGenerator::IExpression> exp = precondStm->GetExpression();
		std::shared_ptr<AbstractTreeGenerator::IStatement> stm = precondStm->GetStatement();

		std::shared_ptr<IRTExpression> expNode = visitChild( exp.get() );
		std::shared_ptr<IRTStatement> stmNode = visitChild( stm.get() );

		std::shared_ptr<Label> beginLabel = std::make_shared<Label>();
		std::shared_ptr<Label> trueLabel = std::make_shared<Label>();
		std::shared_ptr<Label> falseLabel = std::make_shared<Label>();

		std::shared_ptr<IRTSSeq> root = std::make_shared<IRTSSeq>( std::make_shared<IRTSSeq>( std::make_shared<IRTSLabel>( beginLabel ),
			std::make_shared<IRTSCjump>( CJUMP_NE,
				expNode,
				std::make_shared<IRTEConst>( 0 ),
				trueLabel,
				falseLabel ) ),
			std::make_shared<IRTSSeq>( std::make_shared<IRTSSeq>( std::make_shared<IRTSSeq>( std::make_shared<IRTSLabel>( trueLabel ),
				stmNode ),
				std::make_shared<IRTSJump>( beginLabel ) ),
				std::make_shared<IRTSLabel>( falseLabel ) ) );

		returnedStatement = root;
		returnValueType = TStdType::ST_Void;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CPrintStatement* const printStm )
	{
		std::shared_ptr<IRTExpression> expression = visitChild( printStm->GetExpression() );
		assert(expression != 0);
		std::shared_ptr<IRTExpList> arguments = std::make_shared<IRTExpList>( expression, nullptr );
		returnedStatement = std::make_shared<Translate::IRTExpConverter>( std::make_shared<IRTECall>(
			std::make_shared<IRTEName>( table->GetPrintLnLabel() ), arguments ) )->ToStatement();
		returnValueType = TStdType::ST_Void;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CProgram* const program )
	{
		visitChild( program->GetMainClass().get() );
		visitChild( program->GetClassDeclarationList().get() );
		returnValueType = TStdType::ST_Void;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CStatementList* const stmList )
	{
		std::shared_ptr<AbstractTreeGenerator::IStatement> head = stmList->GetStatement();
		std::shared_ptr<AbstractTreeGenerator::CStatementList> tail = stmList->GetStatementList();

		std::shared_ptr<IRTStatement> headNode = visitChild( head.get() );

		std::shared_ptr<IRTStatement> root;

		if( tail != nullptr ) {
			tail->Accept( this );
			std::shared_ptr<IRTStatement> tailNode = returnedStatement;
			assert( tailNode != 0 );
			root = std::make_shared<IRTSSeq>( headNode, tailNode );
		} else {
			root = headNode;
		}

		returnedStatement = root;
		returnValueType = TStdType::ST_Void;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CBasicType* const basicType )
	{
		// not used in building IRTree
		assert( false );
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CIdType* const idType )
	{
		// not used in building IRTree
		assert( false );
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CVarDeclaration* const variable )
	{
		int name = variable->GetIdExpression()->GetName();
		AbstractTreeGenerator::IType* type = variable->GetType().get();
		int typenum = type->GetType();
		currentFrame->InsertVariable( name, std::make_shared<IAccess>( name, typenum ) );
		returnValueType = TStdType::ST_Void;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CVarDeclarationList* const variables )
	{
		visitChild( variables->GetVarDeclaration().get() );
		visitChild( variables->GetVarDeclarationList().get() );
		returnValueType = TStdType::ST_Void;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CTrueExpression* const trueExp )
	{
		std::shared_ptr<IRTEConst> root = std::make_shared<IRTEConst>( IRT_TRUE );
		returnValueType = TStdType::ST_Bool;
		returnedExpression = root;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CFalseExpression* const falseExp )
	{
		std::shared_ptr<IRTEConst> root = std::make_shared<IRTEConst>( IRT_FALSE );
		returnValueType = TStdType::ST_Bool;
		returnedExpression = root;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CGetFieldExpression* const fieldExp )
	{
		std::shared_ptr<AbstractTreeGenerator::IExpression> exp = fieldExp->GetExpression();
		std::shared_ptr<AbstractTreeGenerator::CExpressionList> expList = fieldExp->GetExpressionList();
		int methodName = fieldExp->GetIdExpression()->GetName();

		std::shared_ptr<IRTExpression> expNode = visitChild( exp.get() );
		int expressionType = returnValueType;
		assert( expressionType != TStdType::ST_Void );
		std::shared_ptr<IRTStatement> root = std::make_shared<IRTSExp>( expNode );

		int currentSearchType = expressionType;
		int methodReturnType = TStdType::ST_Void;
		std::shared_ptr<Label>methodLabel = 0;
		do {
			SymbolTable::CClassInfo info = table->GetClassInfo( currentSearchType );
			if( info.ContainsMethod( methodName ) ) {
				SymbolTable::CMethodInfo methodInfo = info.GetMethodInfo( methodName );
				methodLabel = methodInfo.GetLabel();
				methodReturnType = methodInfo.GetReturnType();
			} else {
				currentSearchType = info.GetExtend();
				assert( currentSearchType != SymbolTable::CClassInfo::NothingExtend );
			}
		} while( methodLabel == 0 );

		std::shared_ptr<IRTEName> name = std::make_shared<IRTEName>( methodLabel );
		std::shared_ptr<IRTExpList> arguments = 0;
		if( expList != 0 ) {
			expList->Accept( this );
			arguments = std::dynamic_pointer_cast<IRTExpList>(returnedExpression);
			assert( arguments != 0 );
		}
		std::shared_ptr<IRTECall> call = std::make_shared<IRTECall>( name, arguments );

		returnedExpression = call;
		returnValueType = methodReturnType;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CConditionStatement* const condStm )
	{
		const std::shared_ptr<AbstractTreeGenerator::IExpression> exp = condStm->GetExpression();
		const std::shared_ptr<AbstractTreeGenerator::IStatement> first = condStm->GetStatementFirst();
		const std::shared_ptr<AbstractTreeGenerator::IStatement> second = condStm->GetStatementSecond();

		std::shared_ptr<IRTExpression> expNode = visitChild( exp.get() );
		std::shared_ptr<IRTStatement> leftNode = visitChild( first.get() );
		std::shared_ptr<IRTStatement> rightNode = visitChild( second.get() );

		std::shared_ptr<Label> trueLabel = std::make_shared<Label>();
		std::shared_ptr<Label> falseLabel = std::make_shared<Label>();
		std::shared_ptr<Label> endLabel = std::make_shared<Label>();

		std::shared_ptr<IRTSSeq> root = std::make_shared<IRTSSeq>( std::make_shared<IRTSCjump>( CJUMP_NE,
			expNode,
			std::make_shared<IRTEConst>( 0 ),
			trueLabel,
			falseLabel ),
			std::make_shared<IRTSSeq>( std::make_shared<IRTSSeq>( std::make_shared<IRTSSeq>( std::make_shared<IRTSLabel>( trueLabel ),
				leftNode ),
				std::make_shared<IRTSJump>( endLabel ) ),
				std::make_shared< IRTSSeq>( std::make_shared< IRTSSeq>( std::make_shared<IRTSLabel>( falseLabel ),
					rightNode ),
					std::make_shared<IRTSLabel>( endLabel ) ) ) );

		returnedStatement = root;
		returnValueType = TStdType::ST_Void;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CThisExpression* const thisExp )
	{
		returnedExpression = std::make_shared<IRTEMem>( currentFrame->GetThisAccess() );
		returnValueType = currentClass;
	}

	void IRTBuilderVisitor::visitChild( AbstractTreeGenerator::INode* const child )
	{
		if( child != nullptr ) {
			child->Accept( this );
		}
	}

	std::shared_ptr<IRTExpression> IRTBuilderVisitor::visitChild( AbstractTreeGenerator::IExpression* const child )
	{
		if( child != nullptr ) {
			child->Accept( this );
			return returnedExpression;
		}
		return nullptr;
	}

	std::shared_ptr<IRTStatement> IRTBuilderVisitor::visitChild( AbstractTreeGenerator::IStatement* const child )
	{
		if( child != nullptr ) {
			child->Accept( this );
			return returnedStatement;
		}
		return nullptr;
	}

	void IRTBuilderVisitor::visitChild( std::shared_ptr<AbstractTreeGenerator::INode> const child )
	{
		visitChild( child.get() );
	}

	std::shared_ptr<IRTExpression> IRTBuilderVisitor::visitChild( std::shared_ptr<AbstractTreeGenerator::IExpression> const child )
	{
		return visitChild( child.get() );
	}

	std::shared_ptr<IRTStatement> IRTBuilderVisitor::visitChild( std::shared_ptr<AbstractTreeGenerator::IStatement> const child )
	{
		return visitChild( child.get() );
	}

	void IRTBuilderVisitor::insertMethodExecution()
	{

	}

	std::shared_ptr<CCodeFragment> IRTBuilderVisitor::GetCode()
	{
		return startPoint;
	}
}