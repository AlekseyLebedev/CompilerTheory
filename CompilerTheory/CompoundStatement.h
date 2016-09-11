#pragma once
#include "stdafx.h"
#include "IStatemnet.h"

namespace FirstTask {
	class CCompoundStatement : public IStatemnet
	{
	public:
		CCompoundStatement(std::shared_ptr<INode> left, std::shared_ptr<INode> right);
		virtual ~CCompoundStatement();

	private:
		std::shared_ptr<INode> leftChild, rightChild;
	};
}