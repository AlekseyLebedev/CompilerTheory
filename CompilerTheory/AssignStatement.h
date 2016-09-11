#pragma once
#include "stdafx.h"
#include "IStatemnet.h"

namespace FirstTask {
	class CAssignStatement : IStatemnet
	{
	public:
		CAssignStatement(const std::string name);
		virtual ~CAssignStatement();

	private:
		std::string variableName;
	};
}