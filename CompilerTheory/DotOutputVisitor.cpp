#include "stdafx.h"
#include "DotOutputVisitor.h"
#include "CompoundStm.h"

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

	void CDotOutputVisitor::Visit(FirstTask::CCompoundStm * statement)
	{
		int current = enterNode("CompoundStatement");
	}

	void CDotOutputVisitor::Visit(FirstTask::CPrintStm *)
	{
		int current = enterNode("CompoundStatement");
	}

	void CDotOutputVisitor::Visit(FirstTask::COpExp *)
	{
		int current = enterNode("CompoundStatement");
	}

	void CDotOutputVisitor::Visit(FirstTask::CNumExp *)
	{
		int current = enterNode("CompoundStatement");
	}

	size_t CDotOutputVisitor::enterNode(const std::string& label) {
		++id;
		dotFile << "\tn" << id << "[lebel=\"" << label << "\"";
		return id;
	}

}