#include "IRTBuilderVisitor.h"

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CArgument* const argument )
{
	int name = argument->GetIdExpression()->GetName();
	currentFrame->InsertVariable( name, new IAccess( name ) );
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CArgumentList* const arguments)
{
	visitChild( arguments->GetArgument().get() );
	visitChild( arguments->GetArgumentList().get() );
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CAssignmentListStatement* const )
{
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CAssignmentStatement* const )
{
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CClassDeclaration* const classdeclaration )
{
	//CFrame* bufferFrame;
	/*auto g = classdeclaration->GetVarDeclarationList();
	auto j = classdeclaration->GetIdExpression();*/
	//CCodeFragment* bufferFragment =  new CCodeFragment(visitChild(classdeclaration->))
	currentClass = classdeclaration->GetIdExpression()->GetName();
	visitChild( classdeclaration->GetMethodDeclarationList().get() );
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CClassDeclarationList* const classlist )
{
	visitChild( classlist->GetClassDeclaration().get() );
	visitChild( classlist->GetClassDeclarationList().get() );
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CClassExtend* const )
{
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CCompoundStatement* const statement )
{
	visitChild( statement->GetStatementList().get() );
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CConstructorExpression* const )
{
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CExpressionList* const expList )
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

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CIdExpression* const )
{
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CIndexExpression* const )
{
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CLastExpressionList* const )
{
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CLengthExpression* const )
{
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CListConstructorExpression* const )
{
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CMainClass* const mainclass )
{
	currentClass = mainclass->GetClassName()->GetName();
	startPoint = new CCodeFragment( visitChild( mainclass->GetStatement().get() ) );
	code = startPoint;
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CMethodDeclaration* const method )
{
	CCodeFragment* bufferFragment = new CCodeFragment(
		visitChild(
			new AbstractTreeGenerator::CCompoundStatement(
				method->GetStatementList().get() ) ) );
	code->SetNext( bufferFragment );
	code = bufferFragment;
	currentFrame = new CFrame(currentClass);
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CMethodDeclarationList* const methodList )
{
	visitChild( methodList->GetMethodDeclaration().get() );
	visitChild( methodList->GetMethodDeclarationList().get() );
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CNegationExpression* const )
{
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CNumberExpr* const numerExp )
{
	IRTEConst* root = new IRTEConst( numerExp->GetValue() );

	returnedExpression = root;
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::COperationExpression* const )
{
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CParenExpression* const parenExpression )
{
	std::shared_ptr<AbstractTreeGenerator::IExpression> exp = parenExpression->GetExpression();

	IRTExpression* expNode = visitChild( exp.get() );

	IRTEMem* root = new IRTEMem( expNode );

	returnedExpression = root;
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CPreconditionStatement* const precondStm )
{
	std::shared_ptr<AbstractTreeGenerator::IExpression> exp = precondStm->GetExpression();
	std::shared_ptr<AbstractTreeGenerator::IStatement> stm = precondStm->GetStatement();

	IRTExpression* expNode = visitChild( exp.get() );
	IRTStatement* stmNode = visitChild( stm.get() );

	IRTree::Label* beginLabel = new Label();
	IRTree::Label* trueLabel = new Label();
	IRTree::Label* falseLabel = new Label();

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
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CPrintStatement* const )
{
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CProgram* const program )
{
	visitChild( program->GetMainClass().get() );
	visitChild( program->GetClassDeclarationList().get() );
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CStatementList* const stmList )
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
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CBasicType* const )
{
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CIdType* const )
{
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CVarDeclaration* const variable)
{
	int name = variable->GetIdExpression()->GetName();
	currentFrame->InsertVariable( name, new IAccess( name ) );
}	

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CVarDeclarationList* const variables)
{
	visitChild( variables->GetVarDeclaration().get() );
	visitChild( variables->GetVarDeclarationList().get() );
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CTrueExpression* const trueExp )
{
	IRTEConst* root = new IRTEConst( IRT_TRUE );

	returnedExpression = root;
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CFalseExpression* const falseExp )
{
	IRTEConst* root = new IRTEConst( IRT_FALSE );

	returnedExpression = root;
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CGetFieldExpression* const )
{
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CConditionStatement* const condStm )
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
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CThisExpression* const )
{
}

void IRTree::IRTBuilderVisitor::visitChild( AbstractTreeGenerator::INode* const child )
{
	if( child != nullptr ) {
		child->Accept( this );
	}
}

IRTree::IRTExpression* IRTree::IRTBuilderVisitor::visitChild( AbstractTreeGenerator::IExpression* const child )
{
	if( child != nullptr ) {
		child->Accept( this );
		return returnedExpression;
	}
	return nullptr;
}

IRTree::IRTStatement* IRTree::IRTBuilderVisitor::visitChild( AbstractTreeGenerator::IStatement* const child )
{
	if( child != nullptr ) {
		child->Accept( this );
		return returnedStatement;
	}
	return nullptr;
}
