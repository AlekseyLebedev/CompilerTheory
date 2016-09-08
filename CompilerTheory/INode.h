#pragma once
__interface IVisitor;

__interface INode {
	virtual void Accept(IVisitor*) = 0;
};