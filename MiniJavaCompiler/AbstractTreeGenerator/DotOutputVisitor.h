#pragma once
#include "IVisitor.h"
#include <string>
#include <fstream>

namespace GraphvizOutput {

	class CDotOutputVisitor : public AbstractTreeGenerator::IVisitor
	{
	public:
		CDotOutputVisitor();
		void Start(std::string filename);
		void Close();
		virtual ~CDotOutputVisitor();

		// Унаследовано через IVisitor
		virtual void Visit(AbstractTreeGenerator::CCompoundStatement *) override;
		virtual void Visit(AbstractTreeGenerator::CPrintStatement *) override;
		virtual void Visit(AbstractTreeGenerator::COperationExpression *) override;
		virtual void Visit(AbstractTreeGenerator::CNumExpression *) override;
		virtual void Visit(AbstractTreeGenerator::CIdExpression *) override;
		virtual void Visit(AbstractTreeGenerator::CLastExpressionList *) override;
		virtual void Visit(AbstractTreeGenerator::CAssignStatement *) override;


	private:
		std::ofstream dotFile;
		size_t id;

		size_t enterNode(const std::string & label);
		void addSubNode(size_t id, const std::string & label, const std::string & postfix = "v");
		void addSubNode(size_t id, const size_t label, const std::string & postfix= "v");
		void addArrrow(const size_t from, const size_t to);
	};
}
