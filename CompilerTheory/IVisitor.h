#pragma once

namespace FirstTask {
	class CCompoundStm;
	class CPrintStatement;
	class COpExp;
	class CNumExpression;

	__interface IVisitor {
	public:
		virtual void Visit(CCompoundStm*) = 0;
		virtual void Visit(CPrintStatement*) = 0;
		virtual void Visit(COpExp*) = 0;
		virtual void Visit(CNumExpression*) = 0;
	};
}