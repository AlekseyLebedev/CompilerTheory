#pragma once

namespace FirstTask {
	class AssignStm
	{
	public:
		AssignStm(const std::string name);
		virtual ~AssignStm();

	private:
		std::string variableName;
	};
}