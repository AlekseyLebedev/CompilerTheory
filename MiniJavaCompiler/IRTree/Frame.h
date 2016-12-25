#pragma once
#include <memory>
#include <map>

#include "Access.h"


namespace IRTree {
	class IRTExpression;
	class Label;

	class CFrame {
	public:
		CFrame(int className, Label* label);
		void InsertVariable(int name, IAccess* access);
		IAccess* GetDataInfo( int name );
		Label* GetLabel();
		IAccess* GetThisAccess();
		static const int ThisName;

	private:
		IAccess* thisAccess;
		std::map<int, IAccess*> variables;
		int className;
		Label* label;
	};
}