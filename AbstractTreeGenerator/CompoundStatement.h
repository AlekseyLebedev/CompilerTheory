#pragma once
#include <memory>
#include "IStatement.h"

namespace FirstTask {
	class CCompoundStatement : public IStatement
	{
	public:
		CCompoundStatement(std::shared_ptr<INode> left, std::shared_ptr<INode> right);
		virtual ~CCompoundStatement();
		virtual void Accept(IVisitor*) override;

		std::shared_ptr<INode> GetLeftChild() const;
		std::shared_ptr<INode> GetRightChild() const;
	private:
		std::shared_ptr<INode> leftChild, rightChild;
	};
}