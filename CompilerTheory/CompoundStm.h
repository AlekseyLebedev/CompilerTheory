#pragma once
#include "stdafx.h"
#include "INode.h"

namespace FirstTask {
	class CompoundStm
	{
	public:
		CompoundStm(std::shared_ptr<INode> left, std::shared_ptr<INode> right);
		virtual ~CompoundStm();

	private:
		std::shared_ptr<INode> leftChild, rightChild;
	};
}