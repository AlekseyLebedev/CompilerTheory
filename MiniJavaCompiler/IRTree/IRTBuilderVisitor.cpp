#include "IRTBuilderVisitor.h"

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CArgument* const cArgument )
{}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CArgumentList* const )
{}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CAssignmentListStatement* const )
{}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CAssignmentStatement* const )
{}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CClassDeclaration* const )
{}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CClassDeclarationList* const )
{}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CClassExtend* const )
{}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CCompoundStatement* const )
{}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CConstructorExpression* const )
{}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CExpressionList* const )
{}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CIdExpression* const )
{}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CIndexExpression* const )
{}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CLastExpressionList* const )
{}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CLengthExpression* const )
{}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CListConstructorExpression* const )
{}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CMainClass* const )
{}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CMethodDeclaration* const )
{}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CMethodDeclarationList* const )
{}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CNegationExpression* const )
{}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CNumberExpr* const numerExp )
{
    IRTEConst* root = new IRTEConst( numerExp->GetValue() );

    nodesExpStack.push( root );
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::COperationExpression* const )
{}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CParenExpression* const parenExpression )
{
    std::shared_ptr<AbstractTreeGenerator::IExpression> exp = parenExpression->GetExpression();

    IRTExpression* expNode = visitChild( exp.get() );

    IRTEMem* root = new IRTEMem( expNode );

    nodesExpStack.push( root );
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

    nodesStmStack.push( root );
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CPrintStatement* const )
{}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CProgram* const )
{}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CStatementList* const stmList )
{
    std::shared_ptr<AbstractTreeGenerator::IStatement> head = stmList->GetStatement();
    std::shared_ptr<AbstractTreeGenerator::CStatementList> tail = stmList->GetStatementList();

    IRTStatement* headNode = visitChild( head.get() );

    IRTStatement* root;

    if( tail != nullptr ) {
        tail->Accept( this );

        IRTStatement* tailNode = nodesStmStack.top();
        root = new IRTSSeq( headNode, tailNode );
    } else {
        root = new IRTSSeq( headNode, nullptr );
    }

    nodesStmStack.push( root );
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CBasicType* const )
{}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CIdType* const )
{}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CVarDeclaration* const )
{}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CVarDeclarationList* const )
{}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CTrueExpression* const trueExp )
{
    IRTEConst* root = new IRTEConst( IRT_TRUE );

    nodesExpStack.push( root );
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CFalseExpression* const falseExp )
{
    IRTEConst* root = new IRTEConst( IRT_FALSE );

    nodesExpStack.push( root );
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CGetFieldExpression* const )
{}

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

    nodesStmStack.push(root);
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CThisExpression* const )
{}

IRTree::IRTExpression* IRTree::IRTBuilderVisitor::visitChild( AbstractTreeGenerator::IExpression* const child )
{
    if( child != nullptr ) {
        child->Accept( this );
        IRTExpression* returnedValue = nodesExpStack.top();
        nodesExpStack.pop();
        return returnedValue;
    }
    return nullptr;
}

IRTree::IRTStatement* IRTree::IRTBuilderVisitor::visitChild( AbstractTreeGenerator::IStatement* const child )
{
    if( child != nullptr ) {
        child->Accept( this );
        IRTStatement* returnedValue = nodesStmStack.top();
        nodesStmStack.pop();
        return returnedValue;
    }
    return nullptr;
}
