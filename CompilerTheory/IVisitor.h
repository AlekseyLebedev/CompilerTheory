#pragma once

namespace FirstTask {
	class CCompoundStm;
	class CPrintStm;
	class COpExp;
	class CNumExp;

	__interface IVisitor {
	public:
		virtual void Visit(CCompoundStm*) = 0;
		virtual void Visit(CPrintStm*) = 0;
		virtual void Visit(COpExp*) = 0;
		virtual void Visit(CNumExp*) = 0;
	};
}