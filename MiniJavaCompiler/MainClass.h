#pragma once
#include <string>


namespace FirstTask {
	class CMainClass
	{
	public:
		CMainClass(std::string _name);
		virtual ~CMainClass();
//		virtual void Accept(IVisitor*) override;

		std::string GetName() const;
	private:
		std::string name;
	};
}
