#include "stdafx.h"
#include "DotOutputVisitor.h"
#include "CompoundStatement.h"

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

	void CDotOutputVisitor::Visit(FirstTask::CCompoundStatement * statement)
	{
		int current = enterNode("CompoundStatement");
	}

	void CDotOutputVisitor::Visit(FirstTask::CPrintStatement *)
	{
		int current = enterNode("CompoundStatement");
	}

	void CDotOutputVisitor::Visit(FirstTask::COperationExpression *)
	{
		int current = enterNode("CompoundStatement");
	}

	void CDotOutputVisitor::Visit(FirstTask::CNumExpression *)
	{
		int current = enterNode("CompoundStatement");
	}

	size_t CDotOutputVisitor::enterNode(const std::string& label) {
		++id;
		dotFile << "\tn" << id << "[lebel=\"" << label << "\"";
		return id;
	}

}