#include "IRTBuilderVisitor.h"

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CArgument* const cArgument )
{

}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CArgumentList* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CAssignmentListStatement* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CAssignmentStatement* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CClassDeclaration* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CClassDeclarationList* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CClassExtend* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CCompoundStatement* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CConstructorExpression* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CExpressionList* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CIdExpression* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CIndexExpression* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CLastExpressionList* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CLengthExpression* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CListConstructorExpression* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CMainClass* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CMethodDeclaration* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CMethodDeclarationList* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CNegationExpression* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CNumberExpr* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::COperationExpression* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CParenExpression* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CPreconditionStatement* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CPrintStatement* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CProgram* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CStatementList* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CBasicType* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CIdType* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CVarDeclaration* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CVarDeclarationList* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CTrueExpression* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CFalseExpression* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CGetFieldExpression* const ) {}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CConditionStatement* const condStm )
{
    const std::shared_ptr<AbstractTreeGenerator::IExpression> exp = condStm->GetExpression();
    const std::shared_ptr<AbstractTreeGenerator::IStatement> first = condStm->GetStatementFirst();
    const std::shared_ptr<AbstractTreeGenerator::IStatement> second = condStm->GetStatementSecond();

    IRTExpression* expNode = visitChildExp( exp.get() );
    IRTStatement* leftNode = visitChildStm( first.get() );
    IRTStatement* rightNode = visitChildStm( second.get() );

    Label* trueLabel = new Label();
    Label* falseLabel = new Label();
    Label* endLabel = new Label();
    
    IRTSSeq* root = new IRTSSeq( new IRTSCjump( CJUMP_NE,
                                                expNode,
                                                new IRTEConst( 0 ),
                                                trueLabel,
                                                falseLabel ),
                                 new IRTSSeq( new IRTSSeq( new IRTSSeq( new IRTSLabel(trueLabel),
                                     leftNode ),
                                                           new IRTSJump( endLabel ) ),
                                              new IRTSSeq( new IRTSSeq( new IRTSLabel( falseLabel ),
                                                                        rightNode ),
                                                           new IRTSLabel( endLabel ) ) ) );

    nodesStmStack.push(root);
}

void IRTree::IRTBuilderVisitor::visit( AbstractTreeGenerator::CThisExpression* const ) {}

IRTree::IRTExpression* IRTree::IRTBuilderVisitor::visitChildExp( AbstractTreeGenerator::INode* const child )
{
    if( child != nullptr ) {
        child->Accept( this );
        IRTExpression* returnedValue = nodesExpStack.top();
        nodesExpStack.pop();
        return returnedValue;
    }
    return nullptr;
}

IRTree::IRTStatement* IRTree::IRTBuilderVisitor::visitChildStm( AbstractTreeGenerator::INode* const child )
{
    if( child != nullptr ) {
        child->Accept( this );
        IRTStatement* returnedValue = nodesStmStack.top();
        nodesStmStack.pop();
        return returnedValue;
    }
    return nullptr;
}
