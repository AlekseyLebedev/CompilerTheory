#include "stdafx.h"
#include "FirstTaskMain.h"

#include "GraphvizLauncher.h"
#include "INode.h"
#include "CompoundStatement.h"
#include "AssignStatement.h"
#include "OperationExpression.h"
#include "NumExpression.h"
#include "PrintStatement.h"
#include "LastExpList.h"
#include "IdExpression.h"

void FirstTask::FirstTaskMain()
{
	std::shared_ptr<INode> root(new CCompoundStatement(
		std::make_shared<IStatemnet>(new CAssignStatement("a",
			std::make_shared<IExpression>(new COperationExpression(
				std::make_shared<IExpression>(new CNumExpression(5)),
				std::make_shared<IExpression>(new CNumExpression(3)),
				COperationExpression::Plus)))),
		std::make_shared<IStatemnet>(new CPrintStatement(
			std::make_shared<IExpression>(new CLastExpList(
				std::make_shared<IExpression>(new CIdExpression("a"))))))));
	//std::shared_ptr<INode> root(0);
	GraphvizOutput::CGraphvizLauncher::Launch(root.get());
}
