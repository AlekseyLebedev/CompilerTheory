#pragma once
#include <memory>
#include <map>

#include "Access.h"
class IRTExpression;


namespace IRTree {
	class CFrame {
	public:
		CFrame();
		void InsertVariable(int name, IAccess* access);
		IAccess* GetDataInfo( int name );
	private:
		std::map<int, IAccess*> variables;
	};
}