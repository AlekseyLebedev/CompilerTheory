#include <string>

#include "DotOutputVisitor.h"

#include "INode.h"
#include "AllNodes.h"

namespace GraphvizOutput {

	CDotOutputVisitor::CDotOutputVisitor() : id(0)
	{
	}

	void CDotOutputVisitor::Start(std::string filename)
	{
		dotFile.open(filename, std::ios_base::out | std::ios_base::trunc);
		dotFile << "digraph G{" << std::endl;
		id = 0;
	}

	void CDotOutputVisitor::Close()
	{
		dotFile << "}" << std::endl;
		dotFile.close();
	}


	CDotOutputVisitor::~CDotOutputVisitor()
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CAssignmentStatement * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CCExpression * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CClassDeclaration * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CClassDeclarationList * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CClassExtend * const )
	{
	}

	void CDotOutputVisitor::visit(AbstractTreeGenerator::CCompoundStatement *const compoundStatement)
	{
		size_t current = enterNode("CompoundStatement");
		compoundStatement->GetLeftChild()->Accept(this);
		addArrrow(current, current + 1);
		size_t rightId = id + 1;
		compoundStatement->GetRightChild()->Accept(this);
		addArrrow(current, rightId);

	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CConstructorExpression * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CPreconditionStatement * const )
	{
	}

	void CDotOutputVisitor::visit(AbstractTreeGenerator::CPrintStatement *const printStatement)
	{
		size_t current = enterNode("PrintStatement");
		printStatement->GetExpression()->Accept(this);
		addArrrow(current, current + 1);
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CProgram * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CStatementList * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CType * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CVarDeclaration * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CVarDeclarationList * const )
	{
	}

	void CDotOutputVisitor::visit(AbstractTreeGenerator::COperationExpression *const operationExpression)
	{
		size_t current = enterNode("OperationExpression");
		operationExpression->GetLeftOperand()->Accept(this);
		addArrrow(current, current + 1);
		switch (operationExpression->GetOperationType())
		{
			case AbstractTreeGenerator::COperationExpression::Divide:
				addSubNode(current, "Divide");
				break;
			case AbstractTreeGenerator::COperationExpression::Plus:
				addSubNode(current, "Plus");
				break;
			case AbstractTreeGenerator::COperationExpression::Minus:
				addSubNode(current, "Minus");
				break;
			case AbstractTreeGenerator::COperationExpression::Times:
				addSubNode(current, "Times");
				break;
		}
		size_t rightId = id + 1;
		operationExpression->GetRightOperand()->Accept(this);
		addArrrow(current, rightId);
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CParenExpression * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CMethodDeclaration * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CMethodDeclarationList * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CNegationExpression * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CNumberExpr * const )
	{
		size_t current = enterNode("NumExpression");
		//addSubNode(current, numExpression->GetValue()->GetStringValue());
		//// TODO: возможно было бы логично получать не строку а интовое значение?
		//addSubNode(current, numExpression->GetValue()->GetValue());
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CExpressionList * const )
	{
	}

	void CDotOutputVisitor::visit(AbstractTreeGenerator::CIdExpression *const idExpression)
	{
		size_t current = enterNode("IdExpression");
		addSubNode(current, idExpression->GetName());
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CIndexExpression * const )
	{
	}

	void CDotOutputVisitor::visit(AbstractTreeGenerator::CLastExpressionList *const lastExpList)
	{
		size_t current = enterNode("LastExpressionList");
		lastExpList->GetExpression()->Accept(this);
		addArrrow(current, current + 1);
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CLengthExpression * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CListConstructorExpression * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CMainClass * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CArgument * const )
	{
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CArgumentList * const )
	{
	}

	void CDotOutputVisitor::visit(AbstractTreeGenerator::CAssignStatement *const assignStatement)
	{
		size_t current = enterNode("AssignStatement");
		addSubNode(current, assignStatement->GetVariableName());
		assignStatement->GetExpression()->Accept(this);
		addArrrow(current, current + 1);
	}

	void CDotOutputVisitor::visit( AbstractTreeGenerator::CAssignmentListStatement * const )
	{
	}


	size_t CDotOutputVisitor::enterNode(const std::string& label) {
		++id;
		dotFile << "\tn" << id << "[label=\"" << label << "\"]" << std::endl;
		return id;
	}

	void CDotOutputVisitor::addSubNode(size_t id, const std::string& label, const std::string& postfix) {
		dotFile << "\tn" << id << postfix << "[label=\"" << label << "\"]" << std::endl;
		dotFile << "\tn" << id << " -> n" << id << postfix << ";" << std::endl;
	}

	void CDotOutputVisitor::addSubNode(size_t id, const size_t label, const std::string& postfix) {
		dotFile << "\tn" << id << postfix << "[label=\"" << label << "\"]" << std::endl;
		dotFile << "\tn" << id << " -> n" << id << postfix << ";" << std::endl;
	}

	void CDotOutputVisitor::addArrrow(const size_t from, const size_t to) {
		dotFile << "\tn" << from << " -> n" << to << ";" << std::endl;
	}
}
