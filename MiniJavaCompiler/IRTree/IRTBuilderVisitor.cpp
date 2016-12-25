#include <cassert>
#include <stack>
#include <map>

#include "IRTBuilderVisitor.h"
#include "..\SymbolTable\ClassInfo.h"
#include "..\AbstractTreeGenerator\Type.h"

using TStdType = AbstractTreeGenerator::TStandardType;

namespace IRTree {

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
		currentFrame->InsertVariable( name, new IAccess( name ) );
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CArgumentList* const arguments )
	{
		visitChild( arguments->GetArgument().get() );
		visitChild( arguments->GetArgumentList().get() );
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CAssignmentListStatement* const )
	{
		assert( false ); // TODO
		returnValueType = TStdType::ST_Void;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CAssignmentStatement* const )
	{
		assert( false ); // TODO
		returnValueType = TStdType::ST_Void;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CClassDeclaration* const classdeclaration )
	{
		//CFrame* bufferFrame;
		/*auto g = classdeclaration->GetVarDeclarationList();
		auto j = classdeclaration->GetIdExpression();*/
		//CCodeFragment* bufferFragment =  new CCodeFragment(visitChild(classdeclaration->))
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
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CCompoundStatement* const statement )
	{
		visitChild( statement->GetStatementList().get() );
		returnValueType = TStdType::ST_Void;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CConstructorExpression* const ctor )
	{

		assert( false ); // TODO
		returnValueType = ctor->GetIdExpression()->GetName();
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CExpressionList* const expList )
	{
		std::shared_ptr<AbstractTreeGenerator::IExpression> head = expList->GetExpression();
		std::shared_ptr<AbstractTreeGenerator::CExpressionList> tail = expList->GetExpressionList();

		IRTExpression* headNode = visitChild( head.get() );

		IRTExpression* root;

		if( tail != nullptr ) {
			tail->Accept( this );

			IRTExpression* tailNode = returnedExpression;
			root = new IRTEEseq( new IRTSExp( headNode ), tailNode );
		} else {
			root = new IRTEEseq( new IRTSExp( headNode ), nullptr );
		}

		returnedExpression = root;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CIdExpression* const )
	{
		assert( false ); // TODO
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CIndexExpression* const indexExp )
	{
		std::shared_ptr<AbstractTreeGenerator::IExpression> first = indexExp->GetExpressionFirst();
		std::shared_ptr<AbstractTreeGenerator::IExpression> second = indexExp->GetExpressionSecond();

		IRTExpression* firstNode = visitChild( first.get() );
		int returnType = returnValueType;
		IRTExpression* secondNode = visitChild( second.get() );
		assert( returnType == TStdType::ST_Int );

		// ???
		// returnedExpression = ...
		assert( false ); // TODO
		returnValueType = returnType;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CLastExpressionList * const )
	{
		assert( false ); // TODO
		returnValueType = TStdType::ST_Void;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CLengthExpression* const )
	{
		assert( false ); // TODO
		returnValueType = TStdType::ST_Int;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CListConstructorExpression* const expression )
	{
		assert( false ); // TODO
		returnValueType = TStdType::ST_Intlist;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CMainClass* const mainclass )
	{
		currentClass = mainclass->GetClassName()->GetName();
		startPoint = new CCodeFragment( visitChild( mainclass->GetStatement().get() ) );
		codeFragment = startPoint;
		returnValueType = TStdType::ST_Void;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CMethodDeclaration* const method )
	{
		CCodeFragment* bufferFragment = new CCodeFragment(
			visitChild(
				new AbstractTreeGenerator::CCompoundStatement(
					method->GetStatementList().get() ) ) );
		codeFragment->SetNext( bufferFragment );
		codeFragment = bufferFragment;
		Label* label = table->GetClassInfo( currentClass ).GetMethodInfo( method->GetIdExpression()->GetName() ).GetLabel();
		currentFrame = new CFrame( currentClass, label );
		returnValueType = TStdType::ST_Void;
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

		IRTExpression* expNode = visitChild( exp.get() );

		IRTStatement* root = new IRTSExp( expNode );

		assert( returnValueType == TStdType::ST_Int );
		returnedStatement = root;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CNumberExpr* const numerExp )
	{
		IRTEConst* root = new IRTEConst( numerExp->GetValue() );
		returnValueType = AbstractTreeGenerator::TStandardType::ST_Int;
		returnedExpression = root;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::COperationExpression* const operExp )
	{
		std::shared_ptr<AbstractTreeGenerator::IExpression> left = operExp->GetLeftOperand();
		AbstractTreeGenerator::COperationExpression::TOperationType operType = operExp->GetOperationType();
		std::shared_ptr<AbstractTreeGenerator::IExpression> right = operExp->GetRightOperand();

		// operType ...

		IRTExpression* leftNode = visitChild( left.get() );
		int leftType = returnValueType;
		IRTExpression* rightNode = visitChild( right.get() );
		assert( leftType == returnValueType );
		assert( returnValueType == TStdType::ST_Int || returnValueType == TStdType::ST_Bool );
		// returnValueType same

		// ...
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CParenExpression* const parenExpression )
	{
		std::shared_ptr<AbstractTreeGenerator::IExpression> exp = parenExpression->GetExpression();

		IRTExpression* expNode = visitChild( exp.get() );

		IRTEMem* root = new IRTEMem( expNode );

		returnedExpression = root;
		assert( false ); // TODO return type
		//returnValueType = ???;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CPreconditionStatement* const precondStm )
	{
		std::shared_ptr<AbstractTreeGenerator::IExpression> exp = precondStm->GetExpression();
		std::shared_ptr<AbstractTreeGenerator::IStatement> stm = precondStm->GetStatement();

		IRTExpression* expNode = visitChild( exp.get() );
		IRTStatement* stmNode = visitChild( stm.get() );

		Label* beginLabel = new Label();
		Label* trueLabel = new Label();
		Label* falseLabel = new Label();

		IRTSSeq* root = new IRTSSeq( new IRTSSeq( new IRTSLabel( beginLabel ),
			new IRTSCjump( CJUMP_NE,
				expNode,
				new IRTEConst( 0 ),
				trueLabel,
				falseLabel ) ),
			new IRTSSeq( new IRTSSeq( new IRTSSeq( new IRTSLabel( trueLabel ),
				stmNode ),
				new IRTSJump( beginLabel ) ),
				new IRTSLabel( falseLabel ) ) );

		returnedStatement = root;
		returnValueType = TStdType::ST_Void;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CPrintStatement* const printStm )
	{
		std::shared_ptr<AbstractTreeGenerator::IExpression> exp = printStm->GetExpression();

		IRTExpression* expNode = visitChild( exp.get() );

		IRTStatement* root = new IRTSExp( expNode );

		returnedStatement = root;
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

		IRTStatement* headNode = visitChild( head.get() );

		IRTStatement* root;

		if( tail != nullptr ) {
			tail->Accept( this );

			IRTStatement* tailNode = returnedStatement;
			root = new IRTSSeq( headNode, tailNode );
		} else {
			root = new IRTSSeq( headNode, nullptr );
		}

		returnedStatement = root;
		returnValueType = TStdType::ST_Void;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CBasicType* const basicType )
	{
		int type = basicType->GetType();
		AbstractTreeGenerator::TStandardType value = basicType->GetValue();
		// ...
		assert( false ); // TODO
		returnValueType = TStdType::ST_Void;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CIdType* const idType )
	{
		int type = idType->GetType();
		std::shared_ptr<AbstractTreeGenerator::IExpression> exp = idType->GetIdExpression();

		IRTExpression* expNode = visitChild( exp.get() );

		// ...
		// IRTStatement* root = new IRTSExp( expNode );
		// returnedStatement = root

		assert( false ); // TODO
		returnValueType = TStdType::ST_Void;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CVarDeclaration* const variable )
	{
		int name = variable->GetIdExpression()->GetName();
		currentFrame->InsertVariable( name, new IAccess( name ) );
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
		IRTEConst* root = new IRTEConst( IRT_TRUE );
		returnValueType = TStdType::ST_Bool;
		returnedExpression = root;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CFalseExpression* const falseExp )
	{
		IRTEConst* root = new IRTEConst( IRT_FALSE );
		returnValueType = TStdType::ST_Bool;
		returnedExpression = root;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CGetFieldExpression* const fieldExp )
	{
		std::shared_ptr<AbstractTreeGenerator::IExpression> exp = fieldExp->GetExpression();
		std::shared_ptr<AbstractTreeGenerator::CExpressionList> expList = fieldExp->GetExpressionList();
		int methodName = fieldExp->GetIdExpression()->GetName();

		IRTExpression* expNode = visitChild( exp.get() );
		int expressionType = returnValueType;
		assert( expressionType != TStdType::ST_Void );
		IRTStatement* root = new IRTSExp( expNode );

		int currentSearchType = expressionType;
		int methodReturnType = TStdType::ST_Void;
		Label* methodLabel = 0;
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

		IRTEName* name = new IRTEName( methodLabel );
		IRTExpList* arguments = 0;
		if( expList != 0 ) {
			expList->Accept( this );
			arguments = dynamic_cast<IRTExpList*>(returnedExpression);
			assert( arguments != 0 );
		}
		IRTECall* call = new IRTECall( name, arguments );

		returnedExpression = call;
		returnValueType = methodReturnType;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CConditionStatement* const condStm )
	{
		const std::shared_ptr<AbstractTreeGenerator::IExpression> exp = condStm->GetExpression();
		const std::shared_ptr<AbstractTreeGenerator::IStatement> first = condStm->GetStatementFirst();
		const std::shared_ptr<AbstractTreeGenerator::IStatement> second = condStm->GetStatementSecond();

		IRTExpression* expNode = visitChild( exp.get() );
		IRTStatement* leftNode = visitChild( first.get() );
		IRTStatement* rightNode = visitChild( second.get() );

		Label* trueLabel = new Label();
		Label* falseLabel = new Label();
		Label* endLabel = new Label();

		IRTSSeq* root = new IRTSSeq( new IRTSCjump( CJUMP_NE,
			expNode,
			new IRTEConst( 0 ),
			trueLabel,
			falseLabel ),
			new IRTSSeq( new IRTSSeq( new IRTSSeq( new IRTSLabel( trueLabel ),
				leftNode ),
				new IRTSJump( endLabel ) ),
				new IRTSSeq( new IRTSSeq( new IRTSLabel( falseLabel ),
					rightNode ),
					new IRTSLabel( endLabel ) ) ) );

		returnedStatement = root;
		returnValueType = TStdType::ST_Void;
	}

	void IRTBuilderVisitor::visit( AbstractTreeGenerator::CThisExpression* const thisExp )
	{
		returnedExpression = new IRTEMem( currentFrame->GetThisAccess() );
		returnValueType = currentClass;
	}

	void IRTBuilderVisitor::visitChild( AbstractTreeGenerator::INode* const child )
	{
		if( child != nullptr ) {
			child->Accept( this );
		}
	}

	IRTExpression* IRTBuilderVisitor::visitChild( AbstractTreeGenerator::IExpression* const child )
	{
		if( child != nullptr ) {
			child->Accept( this );
			return returnedExpression;
		}
		return nullptr;
	}

	IRTStatement* IRTBuilderVisitor::visitChild( AbstractTreeGenerator::IStatement* const child )
	{
		if( child != nullptr ) {
			child->Accept( this );
			return returnedStatement;
		}
		return nullptr;
	}
}