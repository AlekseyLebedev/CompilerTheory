#pragma once

#include <stack>
#include <map>

#include "IRTreeAllClasses.h"
#include "Translate.h"
#include "CodeFragment.h"

#include "..\AbstractTreeGenerator\IVisitor.h"
#include "..\AbstractTreeGenerator\AllNodes.h"
#include "Frame.h"

namespace IRTree {

    class IRTBuilderVisitor : public AbstractTreeGenerator::IVisitor
    {
    public:

        // Унаследовано через IVisitor
        virtual void visit( AbstractTreeGenerator::CArgument* const ) override;

        virtual void visit( AbstractTreeGenerator::CArgumentList* const ) override;

        virtual void visit( AbstractTreeGenerator::CAssignmentListStatement* const ) override;

        virtual void visit( AbstractTreeGenerator::CAssignmentStatement* const ) override;

        virtual void visit( AbstractTreeGenerator::CClassDeclaration* const ) override;

        virtual void visit( AbstractTreeGenerator::CClassDeclarationList* const ) override;

        virtual void visit( AbstractTreeGenerator::CClassExtend* const ) override;

        virtual void visit( AbstractTreeGenerator::CCompoundStatement* const ) override;

        virtual void visit( AbstractTreeGenerator::CConstructorExpression* const ) override;

        virtual void visit( AbstractTreeGenerator::CExpressionList* const ) override;

        virtual void visit( AbstractTreeGenerator::CIdExpression* const ) override;

        virtual void visit( AbstractTreeGenerator::CIndexExpression* const ) override;

        virtual void visit( AbstractTreeGenerator::CLastExpressionList* const ) override;

        virtual void visit( AbstractTreeGenerator::CLengthExpression* const ) override;

        virtual void visit( AbstractTreeGenerator::CListConstructorExpression* const ) override;

        virtual void visit( AbstractTreeGenerator::CMainClass* const ) override;

        virtual void visit( AbstractTreeGenerator::CMethodDeclaration* const ) override;

        virtual void visit( AbstractTreeGenerator::CMethodDeclarationList* const ) override;

        virtual void visit( AbstractTreeGenerator::CNegationExpression* const ) override;

        virtual void visit( AbstractTreeGenerator::CNumberExpr* const ) override;

        virtual void visit( AbstractTreeGenerator::COperationExpression* const ) override;

        virtual void visit( AbstractTreeGenerator::CParenExpression* const ) override;

        virtual void visit( AbstractTreeGenerator::CPreconditionStatement* const ) override;

        virtual void visit( AbstractTreeGenerator::CPrintStatement* const ) override;

        virtual void visit( AbstractTreeGenerator::CProgram* const ) override;

        virtual void visit( AbstractTreeGenerator::CStatementList* const ) override;

        virtual void visit( AbstractTreeGenerator::CBasicType* const ) override;

        virtual void visit( AbstractTreeGenerator::CIdType* const ) override;

        virtual void visit( AbstractTreeGenerator::CVarDeclaration* const ) override;

        virtual void visit( AbstractTreeGenerator::CVarDeclarationList* const ) override;

        virtual void visit( AbstractTreeGenerator::CTrueExpression* const ) override;

        virtual void visit( AbstractTreeGenerator::CFalseExpression* const ) override;

        virtual void visit( AbstractTreeGenerator::CGetFieldExpression* const ) override;

        virtual void visit( AbstractTreeGenerator::CConditionStatement* const ) override;

        virtual void visit( AbstractTreeGenerator::CThisExpression* const ) override;


    private:

		void visitChild( AbstractTreeGenerator::INode * const child );
        IRTExpression* visitChild( AbstractTreeGenerator::IExpression* const child );
        IRTStatement* visitChild( AbstractTreeGenerator::IStatement* const child );
		
		IRTExpression* returnedExpression;
		IRTStatement* returnedStatement;
		CCodeFragment* code;
		CCodeFragment* startPoint;
		CFrame* currentFrame;
    };
}
