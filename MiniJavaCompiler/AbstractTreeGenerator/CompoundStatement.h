#pragma once
#include <memory>
#include "IStatement.h"
#include "StatementList.h"

namespace AbstractTreeGenerator {
	class CCompoundStatement : public IStatement {
	public:
		CCompoundStatement( INode* left, INode* right );
		CCompoundStatement( std::shared_ptr<CStatementList> theStatementList = nullptr );
		virtual ~CCompoundStatement();
		virtual void Accept( IVisitor* ) override;

		std::shared_ptr<INode> GetLeftChild() const;
		std::shared_ptr<INode> GetRightChild() const;
		const std::shared_ptr<INode> GetLeftChild,() const;
		const std::shared_ptr<CStatementList> GetStatementList() const;
	private:
		std::shared_ptr<INode> leftChild, rightChild;
		std::shared_ptr<CStatementList> statementList;
	};
}
