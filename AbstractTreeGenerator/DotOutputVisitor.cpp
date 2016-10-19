#include "DotOutputVisitor.h"

#include "INode.h"
#include "CompoundStatement.h"
#include "AssignStatement.h"
#include "OperationExpression.h"
#include "NumExpression.h"
#include "PrintStatement.h"
#include "LastExpressionList.h"
#include "IdExpression.h"

#include <string>

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

	void CDotOutputVisitor::Visit(FirstTask::CCompoundStatement * compoundStatement)
	{
		size_t current = enterNode("CompoundStatement");
		compoundStatement->GetLeftChild()->Accept(this);
		addArrrow(current, current + 1);
		size_t rightId = id + 1;
		compoundStatement->GetRightChild()->Accept(this);
		addArrrow(current, rightId);

	}

	void CDotOutputVisitor::Visit(FirstTask::CPrintStatement *printStatement)
	{
		size_t current = enterNode("PrintStatement");
		printStatement->GetExpression()->Accept(this);
		addArrrow(current, current + 1);
	}

	void CDotOutputVisitor::Visit(FirstTask::COperationExpression *operationExpression)
	{
		size_t current = enterNode("OperationExpression");
		operationExpression->GetLeftOperand()->Accept(this);
		addArrrow(current, current + 1);
		switch (operationExpression->GetOperationType())
		{
			case FirstTask::COperationExpression::Divide:
				addSubNode(current, "Divide");
				break;
			case FirstTask::COperationExpression::Plus:
				addSubNode(current, "Plus");
				break;
			case FirstTask::COperationExpression::Minus:
				addSubNode(current, "Minus");
				break;
			case FirstTask::COperationExpression::Times:
				addSubNode(current, "Times");
				break;
		}
		size_t rightId = id + 1;
		operationExpression->GetRightOperand()->Accept(this);
		addArrrow(current, rightId);
	}

	void CDotOutputVisitor::Visit(FirstTask::CNumExpression *numExpression)
	{
		size_t current = enterNode("NumExpression");
		//addSubNode(current, numExpression->GetValue()->GetStringValue());
		//// TODO: возможно было бы логично получать не строку а интовое значение?
		//addSubNode(current, numExpression->GetValue()->GetValue());
	}

	void CDotOutputVisitor::Visit(FirstTask::CIdExpression *idExpression)
	{
		size_t current = enterNode("IdExpression");
		addSubNode(current, idExpression->GetName());
	}

	void CDotOutputVisitor::Visit(FirstTask::CLastExpressionList *lastExpList)
	{
		size_t current = enterNode("LastExpressionList");
		lastExpList->GetExpression()->Accept(this);
		addArrrow(current, current + 1);
	}

	void CDotOutputVisitor::Visit(FirstTask::CAssignStatement *assignStatement)
	{
		size_t current = enterNode("AssignStatement");
		addSubNode(current, assignStatement->GetVariableName());
		assignStatement->GetExpression()->Accept(this);
		addArrrow(current, current + 1);
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
