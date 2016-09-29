#pragma once
#include "IStatemnet.h"
#include <memory>

namespace FirstTask {
	class CCompoundStatement : public IStatemnet
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