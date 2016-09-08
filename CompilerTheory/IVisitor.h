#pragma once

struct CCompoundStm;
struct CPrintStm;
struct COpExp;
struct CNumExp;

__interface IVisitor {
	virtual void Visit(CCompoundStm*) = 0;
	virtual void Visit(CPrintStm*) = 0;
	virtual void Visit(COpExp*) = 0;
	virtual void Visit(CNumExp*) = 0;
};