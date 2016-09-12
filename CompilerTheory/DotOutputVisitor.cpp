#include "stdafx.h"
#include "DotOutputVisitor.h"

#include "INode.h"
#include "CompoundStatement.h"
#include "AssignStatement.h"
#include "OperationExpression.h"
#include "NumExpression.h"
#include "PrintStatement.h"
#include "LastExpList.h"
#include "IdExpression.h"

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
		size_t current = enterNode("CompoundStatement");
		printStatement->GetExpression()->Accept(this);
		addArrrow(current, current + 1);
	}

	void CDotOutputVisitor::Visit(FirstTask::COperationExpression *operationExpression)
	{
		size_t current = enterNode("OperationExpression");
		operationExpression->GetLeftOperand()->Accept(this);
		addArrrow(current, current + 1);
		size_t rightId = id + 1;
		operationExpression->GetRightOperand()->Accept(this);
		addArrrow(current, rightId);
	}

	void CDotOutputVisitor::Visit(FirstTask::CNumExpression *numExpressio)
	{
		size_t current = enterNode("NumExpression");
	}

	void CDotOutputVisitor::Visit(FirstTask::CIdExpression *idExpression)
	{
		size_t current = enterNode("IdExpression");
	}

	void CDotOutputVisitor::Visit(FirstTask::CLastExpList *lastExpList)
	{
		size_t current = enterNode("LastExpList");
	}

	void CDotOutputVisitor::Visit(FirstTask::CAssignStatement *assignStatement)
	{
		size_t current = enterNode("AssignStatement");
	}


	size_t CDotOutputVisitor::enterNode(const std::string& label) {
		++id;
		dotFile << "\tn" << id << "[label=\"" << label << "\"]" << std::endl;
		return id;
	}

	void CDotOutputVisitor::addArrrow(const int from, const int to) {
		dotFile << "\tn" << from << " -> n" << to << ";" << std::endl;
	}
}
