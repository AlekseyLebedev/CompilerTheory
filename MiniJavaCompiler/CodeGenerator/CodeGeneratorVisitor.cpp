#include <cassert>]

#include "CodeGeneratorVisitor.h"

namespace CodeGeneration {

	void CCodeGeneratorVisitor::startVisit()
	{
		assert( returnValue == 0 );
	}

	void CCodeGeneratorVisitor::startMethod()
	{
		assert( returnValue == 0 );
	}

} // namespace CodeGeneration
